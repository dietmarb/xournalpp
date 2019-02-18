#include "XojMsgBox.h"

#include <i18n.h>

GtkWindow* defaultWindow = NULL;

/**
 * Set window for messages without window
 */
void XojMsgBox::setDefaultWindow(GtkWindow* win)
{
	defaultWindow = win;
}


void XojMsgBox::showErrorToUser(GtkWindow* win, string msg)
{
	if (win == NULL)
	{
		win = defaultWindow;
	}

	GtkWidget* dialog = gtk_message_dialog_new(win, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
											   "%s", msg.c_str());
	if (win != NULL)
	{
		gtk_window_set_transient_for(GTK_WINDOW(dialog), win);
	}
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

int XojMsgBox::showPluginMessage(string pluginName, string msg, int type, bool error)
{
	string header = string("Xournal++ Plugin «") + pluginName + "»";

	if (error)
	{
		header = "Error in " + header;
	}

	GtkWidget* dialog = gtk_message_dialog_new(defaultWindow, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_NONE,
											   "%s", header.c_str());
	if (defaultWindow != NULL)
	{
		gtk_window_set_transient_for(GTK_WINDOW(dialog), defaultWindow);
	}

	GValue val = G_VALUE_INIT;
	g_value_init(&val, G_TYPE_STRING);
	g_value_set_string(&val, msg.c_str());
	g_object_set_property(G_OBJECT(dialog), "secondary-text", &val);
	g_value_unset(&val);

	if (MSG_BT_OK & type)
	{
		gtk_dialog_add_button(GTK_DIALOG(dialog), _("OK"), MSG_BT_OK);
	}
	if (MSG_BT_YES & type)
	{
		gtk_dialog_add_button(GTK_DIALOG(dialog), _("Yes"), MSG_BT_YES);
	}
	if (MSG_BT_NO & type)
	{
		gtk_dialog_add_button(GTK_DIALOG(dialog), _("No"), MSG_BT_NO);
	}
	if (MSG_BT_CANCEL & type)
	{
		gtk_dialog_add_button(GTK_DIALOG(dialog), _("Cancel"), MSG_BT_CANCEL);
	}

	int res = gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	return res;
}

int XojMsgBox::replaceFileQuestion(GtkWindow* win, string msg)
{
	GtkWidget* dialog = gtk_message_dialog_new(win, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_NONE,
											   "%s", msg.c_str());
	if (win != NULL)
	{
		gtk_window_set_transient_for(GTK_WINDOW(dialog), win);
	}
	gtk_dialog_add_button(GTK_DIALOG(dialog), _("Select another name"), 1);
	gtk_dialog_add_button(GTK_DIALOG(dialog), _("Replace"), 2);
	int res = gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	return res;
}

#define XOJ_HELP "https://github.com/xournalpp/xournalpp/wiki/User-Manual"

void XojMsgBox::showHelp(GtkWindow* win)
{
	GError* error = NULL;
	gtk_show_uri(gtk_window_get_screen(win), XOJ_HELP, gtk_get_current_event_time(), &error);

	if (error)
	{
		string msg = FS(_F("There was an error displaying help: {1}") % error->message);
		XojMsgBox::showErrorToUser(win, msg);

		g_error_free(error);
	}
}

