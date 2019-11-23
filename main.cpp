#include<iostream>
#include<iomanip>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include <windows.h>
#include <mysql.h>
#include <sstream>

using namespace std;

int chooseMain();
void getDoctorDatabase();
void getPatientDatabase();
void getBedcount();
//void getPatientReport();

//the doctor class
class doctor{
	public:
	string d_fname,d_lname;
	int d_ID, d_age,experience,d_totalno;
	string qual,d_city;
	string getSpec();
   	friend void addDoc();
   	friend void editDoc(doctor &docobj);
   	friend void displayDoc();
   	friend void deleteDoc();
   	friend void dispDatabase();
   	friend void numberofDocs();
   	friend void getDoctorDatabase();
};
 string doctor::getSpec(){
 	string sp;
	cout<<"1.GENERAL_MEDICINE"<<endl;
	cout<<"2.NEUROLOGY"<<endl;
	cout<<"3.ONCOLOGY"<<endl;
	cout<<"4.HAEMATOLOGY"<<endl;
	cout<<"5.GASTROENTEROLOGY"<<endl;
	cout<<"6.GYNAECOLOGY "<<endl;
	int s;
	cin>>s;
	switch(s){

		case 1:{
			sp= "GENERAL_MEDICINE";
			break;
		}
		case 2:{
			sp="NEUROLOGY";
			break;
		}
		case 3:{
		    sp="ONCOLOGY";
			break;
		}
		case 4:{
			sp= "HAEMATOLOGY";
			break;
		}
		case 5:{
			sp= "GASTROENTEROLOGY";
			break;
		}
		case 6:{
			sp= "GYNAECOLOGY ";
			break;
		}
		default:{
			cout<<"\nCome on!Enter a valid option."<<endl;

		}

	}
		return sp;

}
//the addDoc function
void addDoc(){
        MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
        if(conn){
            cout<< "Connected";
        }
        else{
            cout<< "Not connected";
        }
	    doctor d;
	    cout<<"Fill up the following details"<<endl;
	    cout<<"ID:"<<endl;
	    cin>>d.d_ID;
   		cout<<"First Name:"<<endl;
   		cin>>d.d_fname;
   		cout<<"Last Name:"<<endl;
   		cin>>d.d_lname;
   		cout<<"Age:"<<endl;
   		cin>>d.d_age;
   		cout<<"Choose Qualification among the following:\n1.MBBS\n2.MD"<<endl;
   		int k;
   		cin>>k;
   		if(k==1)
   			d.qual="MBBS";
		else d.qual="MD";
		cout<<"Choose Specialization among the following:"<<endl;
		string spec=d.getSpec();
		cout<<"Experience (in Years):"<<endl;
		cin>>d.experience;
		cout<<"City:"<<endl;
		cin>>d.d_city;
		system("cls");

        int qstate = 0;
        stringstream ss;
        ss << "INSERT INTO doctor(id,fname,lname,age,qualification,specialization,experience,city) VALUES("<<d.d_ID<<",'" << d.d_fname << "','"<<d.d_lname<< "',"<<d.d_age<<",'"<<d.qual<<"','"<<spec<<"',"<<d.experience<<",'"<<d.d_city<<"')";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
        }else{
            cout<<"Failed"<<endl;
        }
	cout<<"\n\t\tNew Doctor profile created successfully!"<<endl<<endl<<endl;
	cout<<"\n\n\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getDoctorDatabase();
	}

	else
	  exit(0);

}

//the editDoc function
void editDoc(doctor &docobj){

    string x;
	cout<<"\nEnter the ID of the Doctor whose profile you want to Edit:"<<endl;
	cin>>x;
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, ("SELECT * FROM doctor WHERE id="+x).c_str());
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout<<"1.ID:"<<row[0]<<endl<<"2.First Name:"<<row[1]<<endl<<"3.Last Name:"<<row[2]<<endl<<"4.Age"<<row[3]<<endl<<"5.Qualification:"<<row[4]<<endl<<"6.Specialization:"<<row[5]<<endl<<"7.Experience:"<<row[6]<<endl<<"8.City:"<<row[7]<<endl<<endl;
            }
        }
        else
            cout<<"\nNo matching records found!"<<endl;

        int edit;
        cout<<"\nEnter number corresponding to the Field you want to Edit:"<<endl<<endl;
        cin>>edit;
        int age,exp;
        string ID,fname,lname,ci,qua,spe;
        int qstate1 = 0;
        stringstream ss1;

	switch(edit)
	{
		case 1:{
			cout<<"ID"<<endl;
			cin>>ID;
			ss1 << "UPDATE doctor SET id = " << ID << " WHERE id = " <<x;
			break;
		}
		case 2:{
			cout<<"First Name:"<<endl;
			cin>>fname;
            ss1 << "UPDATE doctor SET fname ='" << fname<< "' WHERE id = " <<x;
			break;
		}
		case 3:{
			cout<<"Last Name:"<<endl;
			cin>>lname;
            ss1 << "UPDATE doctor SET lname ='" << lname<< "' WHERE id = " <<x;
			break;
		}
		case 4:{cout<<"Age:"<<endl;
			cin>>age;
			ss1 << "UPDATE doctor SET age = " << age << " WHERE id = " <<x;
			break;
		}
		case 5:{
			cout<<"Choose Qualification among the following:\n1.MBBS\n2.MD"<<endl;
   		int q;
   		cin>>q;
   		if(q==1){
		   	qua="MBBS";
		   }

		else {
			qua="MD";
		}
        ss1 << "UPDATE doctor SET qualification = '" << qua<< "' WHERE id = " <<x;
		break;
		}
		case 6:{
			system("cls");
			spe=docobj.getSpec();
			ss1 << "UPDATE doctor SET specialization = '" << spe<< "' WHERE id = " <<x;
			break;
		}
		case 7:{cout<<"Experience:"<<endl;
			cin>>exp;
			ss1 << "UPDATE doctor SET experience = " << exp << " WHERE id = " <<x;
			break;
		}
		case 8:{cout<<"City:"<<endl;
			cin>>ci;
			ss1 << "UPDATE doctor SET city = '" << ci << "' WHERE id = " <<x;
			break;
		}
		default:{
		cout<<"Invalid Input!"<<endl;
		exit(0);
		}
	}
	string query1 = ss1.str();
    const char* q1 = query1.c_str();
    qstate1 = mysql_query(conn, q1);
    if(qstate1 == 0){
            cout << "Record Updated..." << endl;
        }else{
            cout << "Insert Error"<< endl;
        }

    }
	cout<<"\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getDoctorDatabase();
	}

	else
	  exit(0);
}


//the displayDoc function
void displayDoc()
{
    string x;
	cout<<"\nEnter the ID of the Doctor whose profile you want to Display:"<<endl;
	cin>>x;
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, ("SELECT * FROM doctor WHERE id="+x).c_str());
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout<<"1.ID:"<<row[0]<<endl<<"2.First Name:"<<row[1]<<endl<<"3.Last Name:"<<row[2]<<endl<<"4.Age"<<row[3]<<endl<<"5.Qualification:"<<row[4]<<endl<<"6.Specialization:"<<row[5]<<endl<<"7.Experience:"<<row[6]<<endl<<"8.City:"<<row[7]<<endl<<endl;
            }
        }
        else
            cout<<"\nNo matching records found!"<<endl;
    }
    cout<<"\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getDoctorDatabase();
	}

	else
	  exit(0);
}


//the deleteDoc function
void deleteDoc(){
    int x;
	cout<<"\nEnter the ID of the Doctor whose profile you want to Delete:"<<endl;
	cin>>x;
	MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    int qstate = 0;
    stringstream ss;
    ss << "DELETE FROM doctor WHERE id="<< x ;
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "Record deleted..." << endl;
    }else{
        cout<<"No matching records found"<<endl;
    }
    cout<<"\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getDoctorDatabase();
	}

	else
	  exit(0);
}


//the dispDatabase function
void dispDatabase(){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int count=0;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    cout<<right<<setw(70)<<setfill(' ')<<"DOCTOR DATABASE"<<endl<<endl;

    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM doctor");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout<<right<<setw(50)<<setfill(' ')<<"Doctor Profile:"<<count<<endl;
                cout<<"1.ID:"<<row[0]<<endl<<"2.First Name:"<<row[1]<<endl<<"3.Last Name:"<<row[2]<<endl<<"4.Age"<<row[3]<<endl<<"5.Qualification:"<<row[4]<<endl<<"6.Specialization:"<<row[5]<<endl<<"7.Experience:"<<row[6]<<endl<<"8.City:"<<row[7]<<endl<<endl;
                count++;
             }

        }
    }
	if(count==0){
		cout<<"\nNo matching records found!"<<endl;
		exit(0);
	}

    cout<<"\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getDoctorDatabase();
	}
	else
	  exit(0);
}


//the numberofDocs function
void numberofDocs(){
    int count=0;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM doctor");

        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
                count++;
             }
        }
    }
	cout<<"\n\n\tThe no. of doctors in the hospital="<<count<<endl<<endl;
	cout<<"\n\nEnter 1 to return to Doctor Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getDoctorDatabase();
	}

	else
	  exit(0);
}


//the patient class
class patient{
	public:
	string fname,lname,occupation,p_city,dis,addDate,relDate;
	int p_age,p_ID;
	long double phnumber,bill;
	string getDept();
	friend void getDoctor();
	friend void addPat();
	friend void editPat(patient &pat);
	friend void displayPat();
	friend void deletePat();
	friend void dispPatDatabase();
	friend void numberofPats();
   	friend void getPatientDatabase();

};
string patient::getDept(){
	string sp;
	cout<<"1.GENERAL_MEDICINE"<<endl;
	cout<<"2.NEUROLOGY"<<endl;
	cout<<"3.ONCOLOGY"<<endl;
	cout<<"4.HAEMATOLOGY"<<endl;
	cout<<"5.GASTROENTEROLOGY"<<endl;
	cout<<"6.GYNAECOLOGY "<<endl<<endl;
	int s;
	cin>>s;
	switch(s){

		case 1:{
			sp= "GENERAL_MEDICINE";
			break;
		}
		case 2:{
			sp="NEUROLOGY";
			break;
		}
		case 3:{
		    sp="ONCOLOGY";
			break;
		}
		case 4:{
			sp= "HAEMATOLOGY";
			break;
		}
		case 5:{
			sp= "GASTROENTEROLOGY";
			break;
		}
		case 6:{
			sp= "GYNAECOLOGY ";
			break;
		}
		default:{
			cout<<"\nCome on!Enter a valid option."<<endl;
			cout<<"\n\n\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
            int d;
            cin>>d;
            if(d==1){
                system("cls");
                getPatientDatabase();	 //backtoPatientMenu
            }
            else
                exit(0);

            }

	}
		return sp;
}

void getDoctor(){
	patient p;
	string dept;
	cout<<"\nEnter the kind of specialization you are looking for:"<<endl<<endl;
	dept=p.getDept();
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    int count=0;
    cout<<"The doctors available with  "<<dept<<" specialization are:"<<endl<<endl;
    if(conn){
        int qstate = mysql_query(conn, ("SELECT * FROM doctor WHERE specialization='"+dept+"'").c_str());
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout<<"\n\n1.ID:"<<row[0] <<endl<<"2.First Name:"<<row[1] <<endl<<"3.Last Name:"<<row[2] <<endl<<"4.Age:"<<row[3] <<endl<<"5.Qualification:"<<row[4] <<endl<<"6.Specialization:"<<row[5] <<endl<<"7.Experience:"<<row[6] <<endl<<"8.City:"<<row[7] <<endl<<endl;
                count++;
             }
        }
        else
            cout<<"Failed";
    }
	if(count==0){
		cout<<"\nNo doctors with this specialization found!"<<endl;
	}
	else
		cout<<"No of doctors with "<<dept<<" specialization:"<<count<<endl;

	cout<<"\n\n\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}

	else
	  exit(0);
}

//the addPat function
void addPat(){
        patient p;
	    cout<<"Fill up the following details"<<endl;
	    cout<<"ID:"<<endl;
	    cin>>p.p_ID;
   		cout<<"First Name:"<<endl;
   		cin>>p.fname;
   		cout<<"Last Name:"<<endl;
   		cin>>p.lname;
   		cout<<"Age:"<<endl;
   		cin>>p.p_age;
		cout<<"Phone No.:"<<endl;
   		cin>>p.phnumber;
   		cout<<"Occupation:"<<endl;
		cin>>p.occupation;
		cout<<"City:"<<endl;
		cin>>p.p_city;
   		cout<<"Disease/Symptoms:"<<endl;
   		cin>>p.dis;
   		cout<<"Admission date  (YYYY-MM-DD):"<<endl;
   		cin>>p.addDate;
   		cout<<"Release date  (YYYY-MM-DD):"<<endl;
   		cin>>p.relDate;
   		cout<<"Total Bill generated:"<<endl;
   		cin>>p.bill;
		cout<<"Kind of Specialization required:"<<endl;
		string dept=p.getDept();
		system("cls");

		MYSQL* conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);

        int qstate = 0;
        stringstream ss;
        ss << "INSERT INTO patient(pat_id,pat_fname,pat_lname,pat_age,phoneno,occupation,city,disease,admission_date,release_date,total_bill,req_specialization) VALUES("<<p.p_ID<<",'" << p.fname << "','"<<p.lname<< "',"<<p.p_age<<","<<p.phnumber<<",'"<<p.occupation<<"','"<<p.p_city<<"','"<<p.dis<<"','"<<p.addDate<<"','"<<p.relDate<<"',"<<p.bill<<",'"<<dept<<"')";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
        }else{
            cout<<"Failed"<<endl;
        }

	cout<<"\n\t\tNew Patient profile created successfully!"<<endl<<endl<<endl;
	cout<<"\n\n\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}

	else
	  exit(0);
}

void editPat(patient &pat){
	string x;
	cout<<"\nEnter the ID of the Patient whose profile you want to Edit:"<<endl;
	cin>>x;
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, ("SELECT * FROM patient WHERE pat_id="+x).c_str());
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout<<"1.ID:"<<row[0]<<endl<<"2.First Name:"<<row[1]<<endl<<"3.Last Name:"<<row[2]<<endl<<"4.Age"<<row[3]<<endl<<"5.Phone No.:"<<row[4]<<endl<<"6.Occupation:"<<row[5]<<endl<<"7.City:"<<row[6]<<endl<<"8.Disease/Symptoms:"<<row[7]<<endl<<"9.Admission date(DD/MM/YYYY):"<<row[8]<<endl<<"10.Release date(DD/MM/YYYY):"<<row[9]<<endl<<"11.Total Bill generated:"<<row[10]<<endl<<"12.Kind of Specialization required:"<<row[11]<<endl<<endl;
             }
        }
        else
            cout<<"\nNo matching records found!"<<endl;

	int edit;
	cout<<"\nEnter number corresponding to the Field you want to Edit:"<<endl<<endl;
	cin>>edit;
	string fname,lname,occupation,p_city,dis,addDate,relDate,dept;
	int p_age,p_ID;
	long double phnumber,bill;
	int qstate1 = 0;
    stringstream ss1;
	switch(edit)
	{
		case 1:{
			cout<<"ID"<<endl;
			cin>>p_ID;
			ss1 << "UPDATE patient SET pat_id = " << p_ID << " WHERE pat_id = " <<x;
			break;
		}
		case 2:{
			cout<<"First Name:"<<endl;
			cin>>fname;
            ss1 << "UPDATE patient SET pat_fname='" << fname << "' WHERE pat_id = " <<x;
			break;
		}
		case 3:{
			cout<<"Last Name:"<<endl;
			cin>>lname;
			ss1 << "UPDATE patient SET pat_lname='" << lname << "' WHERE pat_id = " <<x;
			break;
		}
		case 4:{cout<<"Age:"<<endl;
			cin>>p_age;
			ss1 << "UPDATE patient SET pat_age = " << p_age << " WHERE pat_id = " <<x;
			break;
		}
		case 5:{
			cout<<"Phone No.:"<<endl;
   			cin>>phnumber;
   			ss1 << "UPDATE patient SET phoneno = " << phnumber << " WHERE pat_id = " <<x;
			break;
		}
		case 6:{
			cout<<"Occupation:"<<endl;
			cin>>occupation;
			ss1 << "UPDATE patient SET occupation='" << occupation << "' WHERE pat_id = " <<x;
			break;
		}
		case 7:{
			cout<<"City:"<<endl;
			cin>>p_city;
			ss1 << "UPDATE patient SET city='" << p_city << "' WHERE pat_id = " <<x;
			break;
		}

		case 8:{
			cout<<"Disease/Symptoms:"<<endl;
			cin>>dis;
			ss1 << "UPDATE patient SET disease='" << dis << "' WHERE pat_id = " <<x;
			break;
		}
		case 9:{
			cout<<"Admission date  (YYYY-MM-DD):"<<endl;
			cin>>addDate;
			ss1 << "UPDATE patient SET admission_date='" << addDate << "' WHERE pat_id = " <<x;
			break;
		}
		case 10:
		{
            cout<<"Release date  (YYYY-MM-DD):"<<endl;
            cin>>relDate;
            ss1 << "UPDATE patient SET release_date='" << relDate << "' WHERE pat_id = " <<x;
            break;
		}
		case 11:{
			cout<<"Total Bill generated:"<<endl;
			cin>>bill;
			ss1 << "UPDATE patient SET total_bill = " << bill << " WHERE pat_id = " <<x;
			break;
		}
		case 12:{
			cout<<"Kind of Specialization required:"<<endl;
			dept=pat.getDept();
			ss1 << "UPDATE patient SET req_specialization='" << dept << "' WHERE pat_id = " <<x;
			break;
		}
		default:{
			cout<<"\nCome on!Enter a valid option."<<endl;
			break;
		}
	}
	string query1 = ss1.str();
    const char* q1 = query1.c_str();
    qstate1 = mysql_query(conn, q1);
    if(qstate1 == 0){
            cout << "Record Updated..." << endl;
        }else{
            cout << "Insert Error"<< endl;
        }

    }
	cout<<"\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}

	else
	  exit(0);

}


//the displayPat function
void displayPat(){
	string x;
	cout<<"\nEnter the ID of the Patient whose profile you want to Display:"<<endl;
	cin>>x;
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, ("SELECT * FROM patient WHERE pat_id="+x).c_str());
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout<<"1.ID:"<<row[0]<<endl<<"2.First Name:"<<row[1]<<endl<<"3.Last Name:"<<row[2]<<endl<<"4.Age"<<row[3]<<endl<<"5.Phone No.:"<<row[4]<<endl<<"6.Occupation:"<<row[5]<<endl<<"7.City:"<<row[6]<<endl<<"8.Disease/Symptoms:"<<row[7]<<endl<<"9.Admission date(DD/MM/YYYY):"<<row[8]<<endl<<"10.Release date(DD/MM/YYYY):"<<row[9]<<endl<<"11.Total Bill generated:"<<row[10]<<endl<<"12.Kind of Specialization required:"<<row[11]<<endl<<endl;
             }

        }
        else
            cout<<"\nNo matching records found!"<<endl;
    }
    cout<<"\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}

	else
	  exit(0);

}


//the deletePat function
void deletePat()
{
    int x;
	cout<<"\nEnter the ID of the Patient whose profile you want to Delete:"<<endl;
	cin>>x;
	MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    int qstate = 0;
    stringstream ss;
    ss << "DELETE FROM patient WHERE pat_id="<< x ;
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "Record deleted..." << endl;
    }else{
        cout<<"No matching records found"<<endl;
    }
    cout<<"\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}

	else
	  exit(0);
}

//the dispPatDatabase function
void dispPatDatabase(){

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int count=0;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    cout<<right<<setw(70)<<setfill(' ')<<"PATIENT DATABASE"<<endl<<endl;

    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM patient");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout<<right<<setw(50)<<setfill(' ')<<"Patient Profile:"<<count<<endl;
                cout<<"1.ID:"<<row[0]<<endl<<"2.First Name:"<<row[1]<<endl<<"3.Last Name:"<<row[2]<<endl<<"4.Age"<<row[3]<<endl<<"5.Phone No.:"<<row[4]<<endl<<"6.Occupation:"<<row[5]<<endl<<"7.City:"<<row[6]<<endl<<"8.Disease/Symptoms:"<<row[7]<<endl<<"9.Admission date(DD/MM/YYYY):"<<row[8]<<endl<<"10.Release date(DD/MM/YYYY):"<<row[9]<<endl<<"11.Total Bill generated:"<<row[10]<<endl<<"12.Kind of Specialization required:"<<row[11]<<endl<<endl;
                count++;
             }

        }
    }
	if(count==0){
		cout<<"\nNo matching records found!"<<endl;
		exit(0);
	}

    cout<<"\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}

	else
	  exit(0);

}

//the numberofPats function
void numberofPats(){
	int count=0;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM patient");

        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
                count++;
             }
        }
    }


	cout<<"\n\n\tThe number of patients in the hospital="<<count<<endl;

    cout<<"\n\nEnter 1 to return to Patient Database\nEnter 2 to Exit."<<endl;
	int c;
	cin>>c;
	if(c==1){
	  system("cls");
	  getPatientDatabase();
	}

	else
	  exit(0);

}



class bed{
	public:
	int total=200;
	friend void getStatus();
};

//the getStatus function
 void getStatus()
 {
    bed b;
    int count=0;
    cout<<"\n\tTotal Number of Beds in the hospital:"<<b.total<<endl;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.43.37", "admin", "admin", "hms", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM patient");

        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                count++;
             }
        }
    }
        cout<<"\n\tThe number of Occupied Beds="<<count<<endl;
        cout<<"\n\tThe number of Empty Beds="<<b.total-count<<endl;

        cout<<"\n\nEnter 1 to return to Bed Database\nEnter 2 to Exit."<<endl;
        int c;
        cin>>c;
        if(c==1){
            system("cls");
            getBedcount();
        }
        else
            exit(0);
 }


//the password class
 class authorizepasswd{

	public:
	string pass;
	void getPassword(){
    cout<<"\nChoose a password for your system:"<<endl;
    cin>>pass;
    }

	int verifyPassword()
	{
	string x;
	cout<<"\nEnter the password:"<<endl;
	cin>>x;
	if (x==pass)
	return 1;
	else
	return 0;
   }

    void passwordProtect(){
    	int veri=verifyPassword();

		 if(veri==1){
		 	cout<<"\nAccess Granted!"<<endl;
		 }
		 else
		 {
		cout<<right<<setw(40)<<setfill(' ')<<"\nAccess Denied!\n\nSystem will shut down\n\nPlease come back again."<<endl;
		 exit(0);
		 }
	}
};


//the main function
int main(){
	authorizepasswd J;
	J.getPassword();
    system("cls");
	cout<<endl;
	cout<<right<<setw(60)<<setfill(' ')<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
	cout<<endl;
	cout<<right<<setw(58)<<setfill(' ')<<"WELCOME TO TCS HOSPITAL MANAGEMENT SYSTEM "<<endl;
	cout<<endl;
	cout<<right<<setw(60)<<setfill(' ')<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
	cout<<endl<<endl;
	cout<<right<<setw(60)<<setfill(' ')<<"------------------------------------------------"<<endl;
	cout<<right<<setw(40)<<setfill(' ')<<"1.Main Menu"<<endl;
	cout<<right<<setw(35)<<setfill(' ')<<"2.Exit"<<endl;
	cout<<right<<setw(60)<<setfill(' ')<<"------------------------------------------------"<<endl<<endl;
	cout<<"Enter your choice:"<<endl<<endl;
	int choice1;
	cin>>choice1;

	if (choice1==1){
		 system("cls");
		 int var=chooseMain();
		 system("cls");

		 	switch(var){
			case 1:{
				J.passwordProtect();
				system("cls");
				getDoctorDatabase();
				break;
			}

			case 2:{
			    J.passwordProtect();
				system("cls");
				getPatientDatabase();
				break;

			}

			case 3:{
			    J.passwordProtect();
				system("cls");
				getBedcount();
				break;
			}

			case 4:
				{
				return 0;
				break;
				}
			default:
				cout<<"\nCome on!Enter a valid option."<<endl;
		}

	}
	else if(choice1==2){
		return 0;
	}
	else
	 cout<<"\nCome on!Enter a valid option."<<endl;
}

//the chooseMain function
int chooseMain(){

	int choice2;
	cout<<endl<<endl;
	cout<<right<<setw(43)<<setfill(' ')<<"MAIN MENU"<<endl<<endl<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;
	cout<<"			"<<"1.Enter Into Doctors' Database"<<endl;
	cout<<"			"<<"2.Enter Into Patients' Database"<<endl;
	cout<<"			"<<"3.Check for Hospital Bed Availability"<<endl;
	cout<<"			"<<"4.Exit"<<endl<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;

	cout<<"\nEnter the number corresponding to your choice:"<<endl;
	cin>>choice2;
	return choice2;

}

//the getDoctorDatabase function
void getDoctorDatabase(){
	int choice_doc;
	cout<<"\n                         " <<"WELCOME TO DOCTOR'S DATABASE"<<endl<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;
	cout<<"			"<<"1.Add New Doctor's Information"<<endl;
	cout<<"			"<<"2.Edit a Doctor's Information"<<endl;
	cout<<"			"<<"3.Display a Doctor's Information"<<endl;
	cout<<"			"<<"4.Delete a Doctor's Information"<<endl;
	cout<<"			"<<"5.Display Entire Doctor Database"<<endl;
	cout<<"			"<<"6.Total Number of Doctors"<<endl;
	cout<<"			"<<"7.Go to patient database"<<endl;
	cout<<"			"<<"8.Exit"<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;

	cout<<right<<setw(60)<<setfill(' ')<<"\nEnter the number corresponding to your choice:"<<endl<<endl;
	cin>>choice_doc;
	system("cls");
	switch(choice_doc){
		case 1:{
		    addDoc();
			break;
		}
		case 2:{
			doctor k;
			editDoc(k);
			break;
		}
		case 3:{
			displayDoc();
			break;
		}
		case 4:{

			deleteDoc();
			break;
		}
		case 5:{

			dispDatabase();
			break;
		}
		case 6:{
			numberofDocs();
			break;
		}
		case 7:{
				system("cls");
				getPatientDatabase();
				break;
        }
		case 8:{
			exit(0);
			break;
		}

	}
}



//the getPatientDatabase function
void	getPatientDatabase(){
	int choice_pat;
	cout<<"\n                         "<<"WELCOME TO PATIENT'S DATABASE"<<endl<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;
	cout<<"			"<<"1.Add New Patient's Information"<<endl;
	cout<<"			"<<"2.Edit a Patient's Information"<<endl;
	cout<<"			"<<"3.Display a Patient's Information"<<endl;
	cout<<"			"<<"4.Delete a Patient's Information"<<endl;
	cout<<"			"<<"5.Display Entire Patient Database"<<endl;
	cout<<"			"<<"6.Total Number of Patients"<<endl;
	cout<<"			"<<"7.Check for doctor availability"<<endl;
	cout<<"			"<<"8.Exit"<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;

	cout<<right<<setw(60)<<setfill(' ')<<"\nEnter the number corresponding to your choice:"<<endl<<endl;
	cin>>choice_pat;
	system("cls");
	switch(choice_pat){
		case 1:{
		    addPat();
			break;
		}
		case 2:{
			patient p;
			editPat(p);
			break;
		}
		case 3:{
			displayPat();
			break;
		}
		case 4:{
			deletePat();
			break;
		}
		case 5:{
			dispPatDatabase();
			break;
		}
		case 6:{
			numberofPats();
			break;
		}
		case 7:{
			getDoctor();
			break;
		}
		case 8:{
			exit(0);
			break;
		}

	}
}

//the getBedDatabase function
void getBedcount(){
    int choice_bed;
	cout<<"\n                    "<<"WELCOME TO BED AVAILABILITY CENTRE"<<endl<<endl;
	cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;
	cout<<"			"<<"1.Check Bed Status"<<endl;
	cout<<"			"<<"2.Exit"<<endl<<endl;
    cout<<right<<setw(80)<<setfill('-')<<"----------"<<endl;

	cout<<right<<setw(60)<<setfill(' ')<<"\nEnter the number corresponding to your choice:"<<endl<<endl;
	cin>>choice_bed;
	system("cls");
	switch(choice_bed)
	{
		case 1:{
		    getStatus();
			break;
		}
		case 2:{
			exit(0);
			break;
		}
	}
}
