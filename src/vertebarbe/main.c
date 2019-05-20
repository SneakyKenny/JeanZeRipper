#include "brute_ite.h"
#include "../purple/hashing/hash.h"
#include <gtk/gtk.h>
#include <string.h>


GtkTextBuffer *B_OUT;
GtkTextBuffer *B_CHARSET;

char *FUNC = "md5";
int NB_THREADS = 8;
int B_MAXLEN = 1;
char *TARGET = "test.txt";

void launch_brut(GtkButton *begin)
{
	GtkTextIter start;
	GtkTextIter end;
	gtk_text_buffer_get_bounds(B_CHARSET, &start, &end);
	char *charset = gtk_text_buffer_get_text(B_CHARSET, &start, &end, FALSE);
	struct BData infos;
	if (strcmp(FUNC, "sha1") == 0)
	{
		infos.hashLen = 40;
		infos.hash_func = sha1_hash_from_string;
	}
	if (strcmp(FUNC, "sha256") == 0)
	{
		infos.hash_func = sha256_hash_from_string;
		infos.hashLen = 64;
	}
	if (strcmp(FUNC, "md5") == 0)
	{
		infos.hash_func = md5_hash_from_string;
		infos.hashLen = 32;
	}
	if (!infos.hash_func)
		return;
	char * result = brut_attack(TARGET, B_MAXLEN, infos, NB_THREADS, charset);
	gtk_text_buffer_set_text(B_OUT, result, strlen(result));
	printf("%s\n",result);
	free(result);
	free(charset);
}


void change_file(GtkFileChooserButton *FileBtn)
{
	TARGET = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(FileBtn));
}


void B_change_len(GtkSpinButton *BLen)
{
	B_MAXLEN = gtk_spin_button_get_value_as_int(BLen);
}


void change_thn(GtkComboBoxText *BThreads)
{
	NB_THREADS = gtk_combo_box_text_get_active_text(BThreads)[0] - '0';
}


void change_func(GtkComboBoxText *combo)
{
	FUNC = gtk_combo_box_text_get_active_text(combo);
}


int main(int argc, char *argv[])
{
	GtkWidget *window;
	gtk_init(&argc, &argv);

	GtkBuilder *builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "JTRMenu.glade", NULL);
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	B_OUT = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "B_OUT"));
	B_CHARSET = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "CHARSET"));

	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));
	gtk_window_maximize(GTK_WINDOW(window));
	gtk_widget_show(window);

	gtk_main();
	return 0;
}
