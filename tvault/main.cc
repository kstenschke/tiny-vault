/*
  Copyright (c) Kay Stenschke
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of  nor the names of its contributors may be used to
     endorse or promote products derived from this software without specific
     prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include <iostream>
#include <gtk/gtk.h>
#include "./vendor/cpp-httplib/httplib.h"

struct appUserData {
  GtkWidget *window;
  GtkWidget *entry_password;
  std::string password = "";
};

appUserData *d;

static gboolean OnKeyDown(GtkWidget *window, GdkEventKey *event, gpointer data)
{
  auto dataStruct = static_cast<appUserData *>(data);

  switch (event->keyval) {
    case GDK_KEY_Escape: case GDK_KEY_Return: {
      if (event->keyval == GDK_KEY_Escape) dataStruct->password = "";

      gtk_widget_destroy(window);
      return TRUE;
    }
    default:
      return FALSE;  // false = event has not been handled, propagate
  }
}

static gboolean OnKeyUp(GtkWidget *window,
                        GdkEventKey *event,
                        gpointer data) {
  auto dataStruct = static_cast<appUserData *>(data);

  if (event->keyval != GDK_KEY_Escape)
    dataStruct->password =
        gtk_entry_get_text(GTK_ENTRY(dataStruct->entry_password));

  return TRUE;
}

static void Activate(GtkApplication* app, gpointer user_data) {
  d = static_cast<appUserData *>(user_data);

  // Setup window
  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "tiny vault");
  gtk_window_set_default_size(GTK_WINDOW(window), 360, 70);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);

  // Add box around UI elements
  GtkWidget *box_outer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
  g_object_set (box_outer, "margin", 8, NULL);
  gtk_container_add(GTK_CONTAINER(window), box_outer);

  // Add box to contain label and input field
  GtkWidget *box_password = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
  gtk_container_add(GTK_CONTAINER(box_outer), box_password);
  // Add label
  GtkWidget *label = gtk_label_new("Secret:");
  g_object_set (label, "margin-right", 8, NULL);
  gtk_box_pack_start(GTK_BOX(box_password), label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box_password), label, TRUE, TRUE, 0);
  // Add input field
  GtkWidget *password = gtk_entry_new();
  gtk_widget_set_hexpand(password, true);
  gtk_entry_set_visibility(GTK_ENTRY(password), 0);
  gtk_container_add(GTK_CONTAINER(box_password), password);

  // Connect window signal handlers
  g_signal_connect(window, "key_press_event", G_CALLBACK(OnKeyDown), d);
  g_signal_connect(window, "key_release_event", G_CALLBACK(OnKeyUp), d);

  // Make elements accessible in app
  d->entry_password = password;

  gtk_widget_show_all(window);
}

bool IsNumeric(const std::string& input) {
  return std::all_of(input.begin(), input.end(), ::isdigit);
}

int main(int argc, char **argv) {
  struct appUserData dataStruct;

  int kPort = argc > 1 && IsNumeric(std::string(argv[1]))
      ? atoi(argv[1])
      : 1234;

  // Setup GTK app
  GtkApplication *app =
      gtk_application_new("org.kstenschke.tvault", G_APPLICATION_FLAGS_NONE);

  // Show and handle popup window: prompt to enter secret string
  g_signal_connect(app, "activate", G_CALLBACK(Activate), &d);

  argc = 0;  // unset arguments (app does not signal-connect to "command-line")
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  if (d->password.empty()) {
    // no password given. exit
    status = 0;
  } else {
    g_print("tvault can now be reached at: http://localhost:%d", kPort);

    // Setup server route
    std::string password = d->password;
    httplib::Server server;
    server.Get("/",
               [password](const httplib::Request &, httplib::Response &res) {
                 res.set_content(password, "text/plain");
               });
    // Start server
    server.listen("localhost", kPort);
  }

  return status;
}
