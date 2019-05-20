#define _GNU_SOURCE
#include "brute_ite.h"
#include "../purple/hashing/hash.h"
#include "../purple/mask/mask.h"
#include <gtk/gtk.h>
#include <string.h>
#include <err.h>
#include <sys/stat.h>
#include <fcntl.h>

GtkTextBuffer *D_OUT;
GtkTextBuffer *B_OUT;
GtkTextBuffer *B_CHARSET;
GtkTextBuffer *M_IN;
GtkTextBuffer *M_OUT;

char *FUNC = "md5";
int NB_THREADS = 8;
int B_MAXLEN = 1;
char *TARGET = "test.txt";
char *DICT = "";
int COMBI = 0;


struct BData get_infos()
{
	struct BData infos;
	if (strcmp(FUNC, "sha1") == 0)
	{
		infos.hashLen = 40;
		infos.hash_func = sha1_hash_from_string;
		infos.func_make_hash = make_sha1;
	}
	if (strcmp(FUNC, "sha256") == 0)
	{
		infos.hash_func = sha256_hash_from_string;
		infos.hashLen = 64;
		infos.func_make_hash = make_sha256;
	}
	if (strcmp(FUNC, "md5") == 0)
	{
		infos.hash_func = md5_hash_from_string;
		infos.hashLen = 32;
		infos.func_make_hash = make_md5;
	}
	if (!infos.hash_func)
		errx(1, "could not create valid infos\n");
	return infos;
}


void sander(char *toFree)
{
	if (toFree == NULL)
		return;
	free(toFree);
}

void print_res(char *result, char c, GtkTextBuffer *B)
{
	char path[] = "output_b.txt";
	char error[] = "Too many results to display!\nYou will find everything in the output file.\n";
	path[7] = c;
	if (strlen(result) < 600)
	{
		gtk_text_buffer_set_text(B, result, strlen(result));
		printf("%s\n", result);
	}
	else
		gtk_text_buffer_set_text(B, error, strlen(error));
	FILE *f = fopen(path, "w");
	fprintf(f, "%s", result);
	fclose(f);
	free(result);
}


void launch_brut(GtkButton *begin)
{
	GtkTextIter start;
	GtkTextIter end;
	gtk_text_buffer_get_bounds(B_CHARSET, &start, &end);
	char *charset = gtk_text_buffer_get_text(B_CHARSET, &start, &end, FALSE);
	struct BData infos = get_infos();
	char *result = brut_attack(TARGET, B_MAXLEN, infos, NB_THREADS, charset);
	print_res(result, 'b', B_OUT);
	free(charset);
}


void launch_dict(GtkButton *begin)
{
	struct BData infos = get_infos();
	char *result = dict_attack(TARGET, DICT, infos);
	print_res(result, 'd', D_OUT);
}

void launch_mask(GtkButton *begin)
{
	GtkTextIter start;
	GtkTextIter end;
	gtk_text_buffer_get_bounds(M_IN, &start, &end);
	char *mask = gtk_text_buffer_get_text(M_IN, &start, &end, FALSE);
	printf("Mask: %s\n", mask);
	struct BData infos = get_infos();
	struct DData file_data = get_data(TARGET);
	int found = 0;
	char *pass = process(mask, &found, file_data.map, file_data.St.st_size, infos);
	
	if (found)
	{
		char *result;
		asprintf(&result, "%s:%s\n", infos.func_make_hash(pass), pass);
		print_res(result, 'm', M_OUT);
	}
	free(pass);
	free(mask);
}

void use_combi(GtkSwitch *sw)
{
	COMBI = gtk_switch_get_state(sw);
}


void change_dict(GtkFileChooserButton *FileBtn)
{
	DICT = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(FileBtn));
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
	D_OUT = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "D_OUT"));
	M_IN = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "M_IN"));
	M_OUT = GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "M_OUT"));

	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));
	gtk_window_maximize(GTK_WINDOW(window));
	gtk_widget_show(window);

	gtk_main();

	return 0;
}
