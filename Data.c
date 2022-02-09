// Nama		: Wildan Setya Nugraha 
// NIM		: 211511032
// Kelas	: 1A - D3 T.Informatika
// M.Kuliah	: Struktur Data & Algoritma Praktek 
// Tanggal	: 9 Februari 2022

#include "Data.h"
#include <stdio.h>
#include <windows.h>

void inputData(){
	Data_a *dt;
	int n,i,j;
	FILE *fp;
	system("cls");
	
	printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("**********************************************************************************************************************\n\n");
	
	printf("Masukkan Jumlah Data yang Diinginkan : ");
	scanf("%d", &n);
	
	fp = fopen("File_a.txt","a");
	dt = (Data_a*)calloc(n,sizeof(Data_a));
	
	
	for(i=0;i<n;i++){
		
		fflush(stdin);
		printf("\nJurusan    : ");
		scanf("%[^\n]s",dt[i].jurusan);
		
		fflush(stdin);
		printf("Prodi      : ");
		scanf("%[^\n]s", dt[i].prodi); 
		
		fflush(stdin);
		printf("Jml Pria   : ");
		scanf("%d",&dt[i].jmlpria);
		
		printf("Jml Wanita : ");
		scanf("%d",&dt[i].jmlwanita);
		
		fwrite(&dt[i], sizeof(Data_a), 1, fp); 
	}
	 
	
	fclose(fp);
	lanjutkan();
}

void cetakData(){
	Data_a dt;
	FILE *fp;
	
	system("cls");
	
	printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("**********************************************************************************************************************\n");
    printf("PRODI | JURUSAN             | JML PRIA | JML WANITA |\n\n");
    
	if((fp = fopen("File_a.txt","r")) == NULL){
		printf("FILE TIDAK TERSEDIA");
		exit(1);
	}
	while(fread(&dt,sizeof(Data_a),1,fp)){
			printf("%-6s| %-20s|    %-5d |     %-5d  |\n",dt.jurusan,dt.prodi,dt.jmlpria,dt.jmlwanita);
	}
	fclose(fp);
	lanjutkan();
}

void urutkanData(){
	Data_a *dt1, dt2;
	FILE *fp;
	int i,j;
	fp = fopen("File_a.txt","r");
	fseek(fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(Data_a);
	dt1 = (Data_a*)calloc(n,sizeof(Data_a));
	
	rewind(fp);
	for(i=0; i<n; i++){
		fread(&dt1[i], sizeof(Data_a), 1, fp);
	}
	
	fclose(fp);
	
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			if(strcmp(dt1[i].jurusan, dt1[j].jurusan)>0){
				dt2 = dt1[i];
				dt1[i] = dt1[j];
				dt1[j] = dt2;
			}
		}
	}
	
	fp = fopen("File_a.txt", "w");
	
	system("cls"); 
	
	printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("**********************************************************************************************************************\n");
    printf("PRODI | JURUSAN             | JML PRIA | JML WANITA |\n\n");
	
	for(i=0;i<n;i++){
		printf("%-6s| %-20s|    %-5d |     %-5d  |\n",dt1[i].jurusan,dt1[i].prodi,dt1[i].jmlpria,dt1[i].jmlwanita);
		fwrite(&dt1[i], sizeof(Data_a), 1, fp);
	}
	printf("\nDATA BERHASIL DIURUTKAN\n");
	fclose(fp);
	lanjutkan(); 
}

void akumulasiData(){
	Data_a *dt;
	FILE *fp;
	int i,j;
	int Tot_prodi_di_jur, Tot_mhs_di_jur, Tot_mhs_mayo_p;
	char var_jur[4];
	
	fp = fopen("File_a.txt","r");

	fseek(fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(Data_a);
	dt = (Data_a*)calloc(n,sizeof(Data_a));
	
	rewind(fp);
	for(i=0;i<n;i++){
		fread(&dt[i],sizeof(Data_a),1,fp);
	}
	
	fclose(fp);
	fp = fopen("File_b.txt","w");
	
	system("cls");
	printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("**********************************************************************************************************************\n");
    printf("PRODI | TOT PRODI | TOT MAYO PRIA | TOT MAHASISWA |\n\n");
	
	i=0;
	j=0;
	while(i<n){
		strcpy(var_jur,dt[i].jurusan);
		Tot_prodi_di_jur = 0;
		Tot_mhs_di_jur = 0;
		Tot_mhs_mayo_p = 0; 
		
		while(j<n && strcmp(dt[i].jurusan,dt[j].jurusan)==0){
			Tot_prodi_di_jur += 1; 
			Tot_mhs_di_jur = Tot_mhs_di_jur + dt[j].jmlpria + dt[j].jmlwanita;
			
			if(dt[j].jmlwanita < dt[j].jmlpria){
				Tot_mhs_mayo_p += 1; 
			}
			j++;
		}
		fprintf(fp,"%s %d %d %d\n",var_jur,Tot_prodi_di_jur, Tot_mhs_di_jur,Tot_mhs_mayo_p);
		printf("%-6s|     %-5d |       %-5d   |      %-5d    |\n",var_jur,Tot_prodi_di_jur,Tot_mhs_mayo_p, Tot_mhs_di_jur);
		i=j;
	}
	fclose(fp);
	lanjutkan(); 
}

void menu(){
	int ch;
	
		system("cls");
		
		printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n\n");
		printf("                   AKUMULASI MAHASISWA\n");
		printf("                      BY WILDAN SN\n\n");
   		printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    	printf("**********************************************************************************************************************\n");
    
		printf("                      1. Input Data\n");
		printf("                      2. Display\n");
		printf("                      3. Urutkan Data\n");
		printf("                      4. Hitung Data\n");
		printf("                      0. Keluar\n");
		
		printf("\n\nPilihan : ");
		scanf("%d", &ch);
		
		switch(ch){
			case 1:
				inputData();
				break;
			case 2:
				cetakData();
				break;
			case 3:
				urutkanData();
				break;
			case 4:
				akumulasiData();
				break;
		}
	
}

void lanjutkan(){
	
	printf("\n\n\t\t[1] MENU & [0] KELUAR : ");
	switch(getch()){
		case '1':
			menu();
			break;
		case '0':
			break;
		default :
			printf("\n\t\tINPUTAN SALAH (TEKAN ENTER!!)");
			getche();
			lanjutkan(); 	
	}
}
