#include "Screen.h"

Screen::Screen(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.stackedWidget->setCurrentIndex(2);
  


    // Hiding Passwords 
    ui.lineEdit_5->setEchoMode(QLineEdit::Password);
    ui.lineEdit_4->setEchoMode(QLineEdit::Password);
    ui.lineEdit_6->setEchoMode(QLineEdit::Password);



    //National ID Validation    
    //home
    ui.lineEdit_3->setValidator(new QDoubleValidator());
    ui.lineEdit_3->setMaxLength(14);
    //user
    ui.lineEdit_2->setValidator(new QDoubleValidator());
    ui.lineEdit_2->setMaxLength(14);
    //search
    ui.lineEdit_11->setValidator(new QDoubleValidator());
    ui.lineEdit_11->setMaxLength(14);
    

    //Three Digits as maximum Age
    ui.lineEdit_8->setValidator(new QIntValidator());
    ui.lineEdit_8->setMaxLength(3);

    string  fnames = "";
    for ( auto it: Stats::firstDoseWaitingList)
    {
        fnames += it.first + " " + it.second + "\n";
    }
    ui.textBrowser->setText(QString::fromStdString(fnames));

    string  snames = "";
    for (auto it : Stats::secondDoseWaitingList)
    {
        snames += it.first + " " + it.second + "\n";
    }
    ui.textBrowser_2->setText(QString::fromStdString(snames));
}

//Home buttons

//SignUp button
void Screen::on_signuplink_2_clicked()
{
    isAdmin = false;
    Clear();
    User_Control();
    ui.stackedWidget->setCurrentIndex(0);

}

//User logIn button
void Screen::on_logIn_clicked()
{
    isAdmin = false;
    UserData* user = Globals::trie->get(ui.lineEdit_3->text().toStdString());


    if (user == nullptr)
    {
        ui.lineEdit_3->clear();
        return;
    }

     if (ui.lineEdit_4->text().toStdString() != user->password) 
     {
         ui.lineEdit_4->clear();
         return;
     }

     currentUserId = user->id;

   //  UserData* CurrentUser = user;

    QString Fname = QString::fromStdString(user->firstName);
    QString Lname = QString::fromStdString(user->lastName);
    QString ID = QString::fromStdString(user->id);
    QString age = QString::number(user->age);
    QString Password = QString::fromStdString(user->password);


    ui.lineEdit->setText(Fname);
    ui.lineEdit_7->setText(Lname);
    ui.lineEdit_2->setText(ID);
    ui.lineEdit_6->setText(Password);
    ui.lineEdit_8->setText(age);

    if (user->isMale)
    {
        ui.radioButton->setChecked(true);
    }
    else
    {
        ui.radioButton_2->setChecked(true);
    }


    if (user->doseCount == 0)
    {
        ui.Not_R_Btn->setChecked(true);
    }
    else if (user->doseCount == 1)
    {
        ui.First_R_Btn->setChecked(true);
    }
    else if (user->doseCount == 2)
    {
        ui.second_R_Btn->setChecked(true);
    }


    for (int i = 0; i < 27; i++)
    {
        if (user->governorate == Stats::governorates[i])
        {
            ui.comboBox->setCurrentIndex(i);
            break;
        }

    }



   
    User_Control();
    ui.stackedWidget->setCurrentIndex(0);
    ui.lineEdit_3->clear();
    ui.lineEdit_4->clear();
}

//Admin logIn button
void Screen::on_logIn_2_clicked()
{
  
   

    if (ui.lineEdit_5->text() == "admin") {
        
        UpdateStats();
        isAdmin = true;
        ui.stackedWidget->setCurrentIndex(1);
    }
    ui.lineEdit_5->clear();
}

void Screen::on_SignUpBtn_clicked()
{
   bool success=Globals::trie->add(createUserFromForm());
   if (success)
   {
       ui.stackedWidget->setCurrentIndex(2);
   }
}

void Screen::on_EditBtn_clicked()
{
   bool success=  Globals::trie->update(currentUserId , createUserFromForm());
    if (success)
    {
        ui.stackedWidget->setCurrentIndex(2);
    }


}

//User form buttons

UserData* Screen::createUserFromForm()
{
    UserData* newUser = new UserData();
    newUser->firstName = ui.lineEdit->text().toStdString();
    newUser->lastName = ui.lineEdit_7->text().toStdString();
    newUser->age = stoi(ui.lineEdit_8->text().toStdString());
    newUser->password = ui.lineEdit_6->text().toStdString();
    newUser->id = ui.lineEdit_2->text().toStdString();
    newUser->governorate = Stats::governorates[ui.comboBox->currentIndex()];
    newUser->isMale = ui.radioButton->isChecked() ? true : false;
    if (ui.Not_R_Btn->isChecked())
    {
        newUser->doseCount = 0;
    }
    else if (ui.First_R_Btn->isChecked())
    {
        newUser->doseCount = 1;
    }
    else
    {
        newUser->doseCount = 2;
    }

    return newUser;
}

//User back Button
void Screen::on_BackBtn_clicked()
{

    if (isAdmin)
    {
 
        ui.stackedWidget->setCurrentIndex(1);
    }
    else
    {
        ui.stackedWidget->setCurrentIndex(2);
    }  
}

//Removing Record
void Screen::on_RemoveBtn_clicked()
{
    Clear();
    Globals::trie->remove(currentUserId);
    UpdateStats();
}

//Stats form button

//Back From Stats to Admin
void Screen::on_backToAdmin_clicked()
{
    ui.stackedWidget->setCurrentIndex(1);

}

//Admin buttons

//advanced stats 
void Screen::on_moreStat_clicked()
{

    vector<pair<string, float>> topLeastGovs = Stats::getTopLeastGoverns();
    ui.label_11->setText(QString::fromStdString(topLeastGovs[0].first));
    ui.label_14->setText(QString::fromStdString(topLeastGovs[1].first));
    ui.label_15->setText(QString::fromStdString(topLeastGovs[2].first));
    ui.label_19->setText(QString::fromStdString(topLeastGovs[3].first));
    ui.label_20->setText(QString::fromStdString(topLeastGovs[4].first));
    ui.label_18->setText(QString::fromStdString(topLeastGovs[5].first));
    ui.progressBar_5->setValue((int)topLeastGovs[0].second);
    ui.progressBar_6->setValue((int)topLeastGovs[1].second);
    ui.progressBar_7->setValue((int)topLeastGovs[2].second);
    ui.progressBar_10->setValue((int)topLeastGovs[3].second);
    ui.progressBar_8->setValue((int)topLeastGovs[4].second);
    ui.progressBar_9->setValue((int)topLeastGovs[5].second);

    ui.stackedWidget->setCurrentIndex(3);


}


//Back
void Screen::on_back_clicked()
{
    Clear();
    isAdmin = false;
    ui.stackedWidget->setCurrentIndex(2);
}

//Search
void Screen::on_search_clicked()
{

    UserData* user = Globals::trie->get(ui.lineEdit_11->text().toStdString());
    string hamada = ui.lineEdit_11->text().toStdString();
    
     if (user==nullptr)
      {
            ui.lineEdit_11->clear();
            return;
      }
       
     currentUserId = user->id;

   QString Fname = QString::fromStdString(user->firstName);
   QString Lname = QString::fromStdString(user->lastName);
   QString ID = QString::fromStdString(user->id);
   QString age = QString::number(user->age);
   QString Password = QString::fromStdString(user->password);


   ui.lineEdit->setText(Fname);
   ui.lineEdit_7->setText(Lname);
   ui.lineEdit_2->setText(ID);
   ui.lineEdit_6->setText(Password);
   ui.lineEdit_8->setText(age);

   if (user->isMale)
   {
       ui.radioButton->setChecked(true);
   }
   else
   {
       ui.radioButton_2->setChecked(true);
   }
   
   
   if (user->doseCount == 0)
   {
       ui.Not_R_Btn->setChecked(true);
   }
   else if (user->doseCount==1)
   {
       ui.First_R_Btn->setChecked(true);
   }else if (user->doseCount == 2)
   {
       ui.second_R_Btn->setChecked(true);
   }


   for (int i = 0; i < 27; i++)
   {
       if (user->governorate == Stats::governorates[i])
       {
           ui.comboBox->setCurrentIndex(i);
           break;
       }

   }
    
    Admin_Control();
    ui.stackedWidget->setCurrentIndex(0);
}




void Screen::on_pushButton_clicked()
{
    ui.stackedWidget->setCurrentIndex(1);

}

void Screen::on_pushButton_2_clicked()
{
    ui.stackedWidget->setCurrentIndex(4);
}

//Save Before Closing
void Screen::closeEvent(QCloseEvent* event)
{
    Globals::trie->saveData();
    event->accept();
}

//Access controls
void Screen::Admin_Control()
{
    if (isAdmin)
    {
        ui.lineEdit->setReadOnly(true);
        ui.lineEdit_2->setReadOnly(true);
        ui.lineEdit_6->setReadOnly(true);
        ui.lineEdit_8->setReadOnly(true);
        ui.lineEdit_7->setReadOnly(true);
        ui.comboBox->setDisabled(true);
        ui.groupBox->setDisabled(true);
        ui.groupBox_2->setDisabled(true);
        ui.EditBtn->setDisabled(true);
        ui.SignUpBtn->setDisabled(true);
    }
}

void Screen::User_Control() 
{
    if (!isAdmin)
    {
        ui.lineEdit->setReadOnly(false);
        ui.lineEdit_2->setReadOnly(false);
        ui.lineEdit_6->setReadOnly(false);
        ui.lineEdit_8->setReadOnly(false);
        ui.lineEdit_7->setReadOnly(false);
        ui.comboBox->setDisabled(false);
        ui.groupBox->setDisabled(false);
        ui.groupBox_2->setDisabled(false);
        ui.EditBtn->setDisabled(false);
        ui.SignUpBtn->setDisabled(false);
    }
}

void Screen::UpdateStats()
{

//Main Statistics

int x1 = Stats::getFullyVaccinatedPerc();
int x2 = Stats::getUnvaccinatedPerc();
int x3 = Stats::getVaccinatedPerc();
int x4 = Stats::getFemalesPerc();

ui.progressBar->setValue(x1);
ui.progressBar_2->setValue(x2);
ui.progressBar_3->setValue(x3);
ui.progressBar_4->setValue(x4);

}

void Screen::Clear()
{
    ui.lineEdit->clear();
    ui.lineEdit_7->clear();
    ui.lineEdit_2->clear();
    ui.lineEdit_6->clear();
    ui.lineEdit_8->clear();

    ui.radioButton->setChecked(false);
    ui.radioButton_2->setChecked(false);
    ui.Not_R_Btn->setChecked(false);
    ui.First_R_Btn->setChecked(false);
    ui.second_R_Btn->setChecked(false);
    ui.comboBox->setCurrentIndex(0);
}

void Screen::Search()
{
    UserData* user;
 

    QString Fname = QString::fromStdString(user->firstName);
    QString Lname = QString::fromStdString(user->lastName);
    QString ID = QString::fromStdString(user->id);
    QString age = QString::number(user->age);
    QString Password = QString::fromStdString(user->password);


    ui.lineEdit->setText(Fname);
    ui.lineEdit_7->setText(Lname);
    ui.lineEdit_2->setText(ID);
    ui.lineEdit_6->setText(Password);
    ui.lineEdit_8->setText(age);

    if (user->isMale)
    {
        ui.radioButton->setChecked(true);
    }
    else
    {
        ui.radioButton_2->setChecked(true);
    }


    if (user->doseCount == 0)
    {
        ui.Not_R_Btn->setChecked(true);
    }
    else if (user->doseCount == 1)
    {
        ui.First_R_Btn->setChecked(true);
    }
    else if (user->doseCount == 2)
    {
        ui.second_R_Btn->setChecked(true);
    }


    for (int i = 0; i < 27; i++)
    {
        if (user->governorate == Stats::governorates[i])
        {
            ui.comboBox->setCurrentIndex(i);
            break;
        }

    }
}