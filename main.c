#include <stdlib.h>
#include <gtk/gtk.h>



 struct login_password{
    GtkWidget *login ;
    GtkWidget *password;
    GtkWindow *login_window;
    GtkWindow *start_window;
  };
struct register_user{
    GtkWidget *name ;
    GtkWidget *surname;
    GtkWindow *login_mail;
    GtkWindow *password;
    GtkWindow *repeat_password;
};

int login_counter = 0 ;

static void close_window (GtkWidget * close_button, GtkWidget * close_window)
{
  gtk_widget_destroy(close_window);
}

static void check_password (GtkWidget *button, gpointer data)
{
 const gchar *LOGIN = "Login" ;
 const gchar *PASSWORD = "Haslo";
 struct login_password * dataptr ;
 dataptr = (struct login_password*) data ;
 GtkWidget *window = NULL;

 if (((strcmp(gtk_entry_get_text(dataptr->login) , LOGIN)==0)) && ((strcmp(gtk_entry_get_text(dataptr->password) , PASSWORD)==0))){
     GtkWidget *window = NULL;
     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title(GTK_WINDOW(window), "Użytkownik zalogowany");
     gtk_widget_destroy(GTK_WIDGET(dataptr->login_window)) ;
     gtk_widget_destroy(GTK_WIDGET(dataptr->start_window)) ;
     gtk_window_set_position(window, GTK_WIN_POS_CENTER);
     gtk_widget_show_all(window);
     }

  else {
     login_counter ++ ;
     if (login_counter >= 3){
        GtkWidget *errorWindow;
        errorWindow = gtk_message_dialog_new(dataptr->login_window,GTK_DIALOG_MODAL,GTK_MESSAGE_ERROR,GTK_BUTTONS_CLOSE, "Przekroczono limit logowan");
        g_signal_connect (errorWindow, "response",G_CALLBACK (gtk_main_quit),NULL);
        gtk_widget_show_all(errorWindow);
     }
     else {
        GtkWidget *OKbutton= NULL;
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "Blad logowania wpisz haslo jeszcze raz");
        OKbutton = gtk_button_new_with_label("OK");
        gtk_widget_set_size_request(window, 300, 100);
        gtk_widget_set_size_request(OKbutton, 0, 0);
        gtk_window_set_position(window, GTK_WIN_POS_CENTER);
        gtk_container_add(GTK_CONTAINER(window), OKbutton);
        g_signal_connect(G_OBJECT(OKbutton), "clicked", G_CALLBACK(close_window), window);
        gtk_widget_show_all(window);
     }
  return;

  }
 return ;
}

static void check_register (GtkWidget *button, gpointer data){
// 1.funkcja sprawdzająca czy użytkownik o danym loginie nie istnieje w bazie danych
// 2.funkcja sprawdzająca czy hasło sie zgadza
// 3.funkcja dodająca do bazy danych nowego użytkowinika
 //struct register_user * dataptr ;
// dataptr = (struct login_password*) data ;
// if (((strcmp(gtk_entry_get_text(dataptr->password), ((strcmp(gtk_entry_get_text(dataptr->repeat_password)))))==0))){
 }

}


static void login (GtkWidget *wid, GtkWidget *wind)
{
  GtkWidget *hbox1, *hbox2, *hbox3 ;
  GtkWidget *vbox = NULL;
  GtkWidget *label_user = NULL;
  GtkWidget *label_password = NULL;
  GtkWidget *entry_name,*entry_password;
  GtkWidget *login_button, *close_button;
  GtkWidget *secondWindow = NULL;

  struct login_password *lp;

  vbox = gtk_vbox_new(TRUE,10);

  label_user = gtk_label_new("Użytkownik:  ");
  label_password = gtk_label_new("Hasło:  ");

  entry_name = gtk_entry_new();
  entry_password = gtk_entry_new();

  secondWindow =gtk_window_new(GTK_WINDOW_TOPLEVEL);
  login_button = gtk_button_new_with_label("Login");
  close_button = gtk_button_new_with_label("Quit");

  gtk_window_set_position(secondWindow, GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(secondWindow), "Logowanie użytkownika");

  hbox1 = gtk_hbox_new(TRUE,10);
  gtk_box_pack_start (GTK_BOX (hbox1),label_user, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (hbox1),entry_name, TRUE, TRUE, 0);

  hbox2 = gtk_hbox_new(TRUE,10);
  gtk_box_pack_start (GTK_BOX (hbox2),label_password, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (hbox2),entry_password, TRUE, TRUE, 0);

  hbox3 = gtk_hbox_new(TRUE,10);
  gtk_box_pack_start (GTK_BOX (hbox3),login_button, TRUE, TRUE, 50);
  gtk_box_pack_start (GTK_BOX (hbox3),close_button, TRUE, TRUE, 50);

  gtk_box_pack_start (GTK_BOX (vbox),hbox1, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox),hbox2, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox),hbox3, TRUE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(secondWindow), vbox);

  lp = g_new0(struct login_password, 1);
  lp->login = entry_name;
  lp->password = entry_password;
  lp->login_window = secondWindow ;
  lp->start_window = wind ;
  g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(check_password), (gpointer)lp);

  g_signal_connect(G_OBJECT(close_button), "clicked", G_CALLBACK(gtk_main_quit), NULL);




  gtk_widget_show_all(secondWindow);
}

static void registerUser (GtkWidget *wid, GtkWidget *wind)
{
  GtkWidget *register_window = NULL ;
  GtkWidget *table;
  GtkWidget *register_button = NULL;
  GtkWidget *hbox;
  struct register_user * ru ;

  GtkWidget *label;

  table = gtk_table_new(5,2,TRUE);

  GtkWidget *entry_name;
  GtkWidget *entry_surname;
  GtkWidget *entry_login;
  GtkWidget *entry_password;
  GtkWidget *entry_repeat_password;
  entry_name = gtk_entry_new();
  entry_surname = gtk_entry_new();
  entry_login = gtk_entry_new();
  entry_password = gtk_entry_new();
  entry_repeat_password = gtk_entry_new();
  register_button = gtk_button_new_with_label("Register");

  GString *values[5] = {"Imię:",
                        "Nazwisko:",
                        "Login/email:",
                        "Hasło:",
                        "Powtórz hasło:"};

  //create new dialoge window to register uster
  register_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (register_window), "Rejestracja użytkownika");
  gtk_window_set_default_size(register_window, 400, 200);
  gtk_window_set_position(register_window, GTK_WIN_POS_CENTER);

  //add table to window
  gtk_container_add(GTK_CONTAINER(register_window), table);

  /*label = gtk_label_new(values[0]);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, 0, 1);*/
  for (int i = 0; i < 5 ; i++){
    label = gtk_label_new(values[i]);
    gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 1, i, i+1);
  }

  gtk_table_attach_defaults(GTK_TABLE(table), entry_name, 1, 2, 0, 1);
  gtk_table_attach_defaults(GTK_TABLE(table), entry_surname, 1, 2, 1, 2);
  gtk_table_attach_defaults(GTK_TABLE(table), entry_login, 1, 2, 2, 3);
  gtk_table_attach_defaults(GTK_TABLE(table), entry_password, 1, 2, 3, 4);
  gtk_table_attach_defaults(GTK_TABLE(table), entry_repeat_password, 1, 2, 4, 5);
  gtk_table_attach_defaults(GTK_TABLE(table), register_button, 0, 2, 5, 6);

  ru = g_new0(struct register_user, 1);
  ru->name = entry_name;
  ru->surname =entry_surname;
  ru->login_mail = entry_login;
  ru->password = entry_password;
  ru->repeat_password = entry_repeat_password;
  g_signal_connect(G_OBJECT(register_button), "clicked", G_CALLBACK(check_register),(gpointer)ru);

  gtk_widget_show_all(register_window);

}



int main (int argc, char *argv[])
{
  gtk_init(&argc, &argv);
  GtkWidget *hbox1, *hbox2, *hbox3 ;
  GtkWidget *window = NULL;
  GtkWidget *button = NULL;
  GtkWidget *vbox = NULL ;
  GtkWidget *label_login = NULL;
  GtkWidget *label_register = NULL;
  GtkWidget *label_question = NULL;

  vbox = gtk_vbox_new (FALSE,0) ;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(window, GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(window, 400,100);
  gtk_window_set_title (GTK_WINDOW (window), "Witamy w ksiegarni");

  label_login = gtk_label_new("Logowanie Użytkowinia:  ");
  button = gtk_button_new_with_label("Zaloguj");
  gtk_widget_set_size_request(button, 200, 25);

  hbox1 = gtk_hbox_new(TRUE,10);
  gtk_box_pack_start (GTK_BOX (hbox1), label_login, FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (hbox1), button, FALSE, FALSE, 10);

  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(login), window);
  label_question = gtk_label_new("Nie masz jeszcze konta?   Zarejestruj sie.");
  hbox2 = gtk_hbox_new(TRUE,10);
  gtk_box_pack_start (GTK_BOX (hbox2), label_question, FALSE, FALSE, 5);

  label_register = gtk_label_new("Rejestracja:  ");
  button = gtk_button_new_with_label("Rejestracja użytkownika");
  gtk_widget_set_size_request(button, 200, 25);

  hbox3 = gtk_hbox_new(TRUE,10);
  gtk_box_pack_start (GTK_BOX (hbox3), label_register, FALSE, FALSE, 5);
  gtk_box_pack_start (GTK_BOX (hbox3), button, FALSE, FALSE, 10);

  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(registerUser), window);

  gtk_box_pack_start (GTK_BOX (vbox),hbox1, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox),hbox2, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (vbox),hbox3, TRUE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
