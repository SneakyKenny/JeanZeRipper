#include "brute_ite.h"
#include "../purple/hashing/hash.h"
#include <gtk/gtk.h>


GtkTextBuffer *B_OUT;
GtkSpinButton *lenInput;
GtkSpinButton *thBinput;
GtkButton *launchB;

int launch_brut(char *func)
{
	struct BData infos;
	if (strcmp(func, "sha1") == 0)
	{
		infos.hashLen = 40;
		infos.hash_func = sha1_hash_from_string;
	}
	if (strcmp(func, "sha256") == 0)
	{
		infos.hash_func = sha256_hash_from_string;
		infos.hashLen = 64;
	}
	if (strcmp(func, "md5") == 0)
	{
		infos.hash_func = md5_hash_from_string;
		infos.hashLen = 32;
	}
	if (!infos.hash_func)
		return 1;
	brut_attack("test.txt", 5, infos);
	return 0;
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	gtk_init(&argc, &argv);

	GtkBuilder *builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "JTRMenu.glade", NULL);
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	lenInput = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "lenInput"));
	thBinput = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "thBinput"));
	launchB = GTK_BUTTON(gtk_builder_get_object(builder, "launchB"));
	B_OUT = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "B_OUT"));

	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));
	gtk_window_maximize(GTK_WINDOW(window));
	gtk_widget_show(window);

	gtk_main();
	launch_brut("md5");
	return 0;
}
