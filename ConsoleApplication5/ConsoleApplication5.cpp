
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLENGTH 100

typedef struct {
	int dd, mm, yy;
}date;

typedef struct {
	int idPatient;
	int age;
	char namePatient[100];
	char genderPatient[100];
	char addressPatient[100];
	char emailPatient[100];
	char tel[100];
	char disease[100];
	date bd, ed;
}patient;

void seeHospitalName();
void seeHospitalInfor();
patient getPatientInfo();
void showPatientInfo(patient A);
int appendtoLsPatients(patient* LsP, int n, patient A);
void showLsPatients(patient* Ls, int n);
void edittoLsPatients(patient* LsP, int n, int position);
int searchPatient_ID(patient* LsP, int n, int ID);
int deleteLsposition(patient* LsP, int n, int position);
void sortLsAge(patient* LsP, int n);
void save_into_file(patient* LsP, int n);
void strcline(char source[], char dest[], int len);

int main()
{
	seeHospitalName();
	seeHospitalInfor();
	patient list[MAXLENGTH]; int current = 0;
	::system("pause");
	::system("cls");
	for (;;)
	{
		int choices;

		printf("\n Please, choose one of these following options: \n");
		printf("\n 1. >> Patient Record List \n");
		printf("\n 2. >> Add Patient Record \n");
		printf("\n 3. >> Update Patient Record\n");
		printf("\n 4. >> Delete Patient Record\n");
		printf("\n 5. >> Sort Patient Record in ascending order of age\n");
		printf("\n 0. >> Exit the program!\n");
		printf("\n Enter your choice : "); scanf_s("%d", &choices);

		if (choices == 1) {
			printf(" Patient Record List: \n");
			printf(" ------------------- \n");
			FILE* f; errno_t err;
			char filename[] = "TextFile5.txt"; //constant
			err = fopen_s(&f, filename, "r");
			if (!err) {
				// read the first line
				char str[256];
				fgets(str, 256, f);
				int num_ele = atoi(str);
				printf(" Number of existing element %d \n", num_ele);
				//loading data
				for (int i = 0; i < num_ele; i++) {
					// create a patient structure and put it in list
					patient pat;
					char line[256];
					fgets(line, 256, f); pat.idPatient = atoi(line);
					fgets(line, 256, f);
					int len = strlen(line);
					char name[254]; strcline(line, name, len - 1); strcpy(pat.namePatient, name);
					fgets(line, 256, f);
					char sex[256]; strcline(line, sex, len - 1); strcpy(pat.genderPatient, sex);
					fgets(line, 256, f); pat.age = atoi(line);
					fgets(line, 256, f);
					char address[256]; strcline(line, address, len - 1); strcpy(pat.addressPatient, address);
					fgets(line, 256, f);
					char telephone[256]; strcline(line, telephone, len - 1); strcpy(pat.tel, telephone);
					fgets(line, 256, f);
					char mail[256]; strcline(line, mail, len - 1); strcpy(pat.emailPatient, mail);
					fgets(line, 256, f);
					char disease_patient[256]; strcline(line, disease_patient, len - 1); strcpy(pat.disease, disease_patient);
					fgets(line, 256, f); pat.bd.dd = atoi(line);
					fgets(line, 256, f); pat.bd.mm = atoi(line);
					fgets(line, 256, f); pat.bd.yy = atoi(line);
					fgets(line, 256, f); pat.ed.dd = atoi(line);
					fgets(line, 256, f); pat.ed.mm = atoi(line);
					fgets(line, 256, f); pat.ed.yy = atoi(line);
					//adding to existing list
					current = appendtoLsPatients(list, current, pat);
				}
			}
			fclose(f);
			printf(" list of patient in file \n");
			showLsPatients(list, current);
			::system("pause");
			::system("cls");
		}
		else if (choices == 2) {
			printf(" Add Patient Record:\n");
			showLsPatients(list, current);
			int req;
			printf(" -----------------\n");
			printf(" Number of patient ");
			scanf_s("%d", &req);
			for (int i = 0; i < req; i++) {
				patient a = getPatientInfo();// get inf of new patient
				current = appendtoLsPatients(list, current, a); // add to the lits
			}
			// show list
			printf(" INSERTED PATIENTS:\n");
			showLsPatients(list, current);

			::system("pause");
			::system("cls");
		}
		else if (choices == 3) {
			printf(" Insert ID of patient you want to change: \n");
			int ID; scanf_s("%d", &ID);
			int position = searchPatient_ID(list, current, ID);
			if (position >= 0)
				edittoLsPatients(list, current, position);
			printf(" INSERTED PATIENTS: \n");
			showLsPatients(list, current);

			::system("pause");
			::system("cls");
		}
		else if (choices == 4) {
			printf(" Insert ID of patient you want to delete: ");
			int del_ID; scanf_s("%d", &del_ID);
			int position = searchPatient_ID(list, current, del_ID);
			if (position >= 0)
				current = deleteLsposition(list, current, position);
			// show list
			printf(" PATIENTS AFTER DELETE:\n");
			showLsPatients(list, current);

			::system("pause");
			::system("cls");
		}
		else if (choices == 5) {
			sortLsAge(list, current);
			printf(" PATIENTS AFTER SORTING \n");
			showLsPatients(list, current);
		}
		else if (choices == 0) {
			save_into_file(list, current);
			break;
		}
	}
}
void seeHospitalName() {
	printf(" Hong Ngoc General Hospital");
	printf("---------------------------");
}
void seeHospitalInfor() {
	printf(" Type: General Hospital\n");
	printf(" Address: 55 Yen Ninh, Truc Bach ward, Ba Dinh district, Hanoi\n");
	printf(" Hotline: 024 3927 5568 ext 0\n");
	printf(" Email: info@hongngochospital.vn\n");
}
patient getPatientInfo() {
	patient a;
	printf(" Insert patient's information: \n");
	printf(" Patient ID: "); scanf_s("%d", &a.idPatient); while (getchar() != '\n');
	printf(" Patient name: "); gets_s(a.namePatient);
	printf(" Gender: "); gets_s(a.genderPatient);
	/*printf(" Birth date: "); scanf_s("%d%d%d", &a.bd.dd, &a.bd.mm, &a.bd.yy); while (getchar() != '\n');*/
	printf(" Age: "); scanf_s("%d", &a.age); while (getchar() != '\n');
	printf(" Patient address: "); gets_s(a.addressPatient);
	printf(" Patient telephone: "); gets_s(a.tel);
	printf(" Patient email: "); gets_s(a.emailPatient);
	printf(" Patient disease: "); gets_s(a.disease);
	printf(" Examination date: "); scanf_s("%d/%d/%d", &a.ed.dd, &a.ed.mm, &a.ed.yy); while (getchar() != '\n');
	return a;
}
void showPatientInfo(patient A) {
	printf(" %d: %s, Gender: %s, Age: %d, Address: %s\n", A.idPatient, A.namePatient, A.genderPatient, A.age, A.addressPatient);
	printf(" Tel: %s, Email: %s\n", A.tel, A.emailPatient);
	printf(" Disease: %s, Examination date: %d/%d/%d\n ", A.disease, A.ed.dd, A.ed.mm, A.ed.yy);
}
int appendtoLsPatients(patient* LsP, int n, patient A) {
	if (n < MAXLENGTH) {
		LsP[n] = A;
		n++;
	}
	else
		printf("The number of patient is over than the maximum");
	return n;
}
void showLsPatients(patient* LsP, int n) {
	for (int i = 0; i < n; i++) {
		printf(" Patient number %d\n", i + 1);
		printf(" -----------------\n");
		showPatientInfo(LsP[i]);
	}
}
void edittoLsPatients(patient* LsP, int n, int position) {
	if (position < MAXLENGTH) {
		printf(" Current information of patient %d \n", n);
		showPatientInfo(LsP[position]);
		printf("Insert updated information \n ");
		patient a;
		a = getPatientInfo();
		LsP[position] = a;
	}
}
int searchPatient_ID(patient* LsP, int n, int ID) {
	for (int i = 0; i < n; i++) {
		if (LsP[i].idPatient == ID)
			return i;
	}
	return -1;
}
int deleteLsposition(patient* LsP, int n, int position) {
	if (position < n) {
		for (int i = position; i < n; i++)
			LsP[i] = LsP[i + 1];
	}
	n--;
	return n;
}
void sortLsAge(patient* LsP, int n) {
	// sort the list by score in asending order
	// using selected sort algorithm ()
	for (int i = 0; i < n; i++) {
		int minpos = i;
		for (int j = i; j < n; j++)
			if (LsP[j].age < LsP[minpos].age)
				minpos = j;
		patient buf = LsP[i];
		LsP[i] = LsP[minpos];
		LsP[minpos] = buf;
	}
}

void strcline(char source[], char dest[], int len) {
	int i = 0;
	for (i = 0; i < len; i++)
		dest[i] = source[i];
	dest[i] = '\0';
}
void save_into_file(patient* LsP, int n) {
	FILE* f; errno_t err;
	char filename[] = "TextFile5.txt";
	err = fopen_s(&f, filename, "w");
	if (!err) {
		//save data from array into file
		//first line
		fprintf(f, "%d\n", n); // number off element
		for (int i = 0; i < n; i++) {
			// save elements
			fprintf(f, "%d\n", LsP[i].idPatient);
			fprintf(f, "%s\n", LsP[i].namePatient);
			fprintf(f, "%s\n", LsP[i].genderPatient);
			fprintf(f, "%d\n", LsP[i].age);
			fprintf(f, "%s\n", LsP[i].addressPatient);
			fprintf(f, "%s\n", LsP[i].tel);
			fprintf(f, "%s\n", LsP[i].emailPatient);
			fprintf(f, "%s\n", LsP[i].disease);
			fprintf(f, "%d\n", LsP[i].ed.dd);
			fprintf(f, "%d\n", LsP[i].ed.mm);
			fprintf(f, "%d\n", LsP[i].ed.yy);
		}
	}
}