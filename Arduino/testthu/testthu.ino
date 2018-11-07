String S1="";String S2="";String S3="";String S4="";String S5="";
String S6="";String S7="";String S9="";String S8="";


void Check_Dele_Sdt(){
  if(RX[i]=='('){
        Serial.println(i);
        Xoa1=i+1;
      }
  if(RX[i]==')'){
        Serial.println(i);
        Xoa2=i;
      } 
}
void Vi_Tri_Xoa(){
  int a=0;int c=0;
  if(Xoa1>0&&Xoa2>0){
    a=RX[Xoa1]-48;
    c=R_Rom(120);
    Sap_Xep_Sdt(a,c);
    S_Rom(120,(c-1)); 
  }
}

void Sap_Xep_Sdt(int a,int c){
  switch(a){
    case 1:
      for(int i=2;i<=c;i++){
        Read(i);
        Save(i-1);
      }
      break;
    case 2:
      for(int i=3;i<=c;i++){
        Read(i);
        Save(i-1);
      }
      break;
    case 3:
      for(int i=4;i<=c;i++){
        Read(i);
        Save(i-1);
      }
      break;
    case 4:
      for(int i=5;i<=c;i++){
        Read(i);
        Save(i-1);
      }
      break;
    case 5:
      for(int i=6;i<=c;i++){
        Read(i);
        Save(i-1);
      }
      break;
    case 6:
      for(int i=7;i<=c;i++){
        Read(i);
        Save(i-1);
      }
      break;
    case 7:
      for(int i=8;i<=c;i++){
        Read(i);
        Save(i-1);
      }
      break;
    case 8:
      for(int i=9;i<=c;i++){
        Read(i);
        Save(i-1);
      }
      break;
    case 9:
      break;
  }
}

void Read(int c){
  switch(c){
    case 1:
      S1=R_SDT(1);break;
    case 2:
      S2=R_SDT(2);break;
    case 3:
      S3=R_SDT(3);break;
    case 4:
      S4=R_SDT(4);break;
    case 5:
      S5=R_SDT(5);break;
    case 6:
      S6=R_SDT(6);break;
    case 7:
      S7=R_SDT(7);break;
    case 8:
      S8=R_SDT(8);break;
    case 9:
      S9=R_SDT(9);break;
  }
}

void Save(int c){
  switch(c){
    case 1:
      S_SDT(1,S2);
      break;
    case 2:
      S_SDT(2,S3);
      break;
    case 3:
      S_SDT(3,S4);
      break;
    case 4:
      S_SDT(4,S5);
      break;
    case 5:
      S_SDT(5,S6);
      break;
    case 6:
      S_SDT(6,S7);
      break;
    case 7:
      S_SDT(7,S8);
      break;
    case 8:
      S_SDT(8,S9);
      break;
  }
}

String All_Sdt(int c){
  String Sdt="";
  switch(c){
    case 1:
      Sdt=S1;break;
    case 2:
      Sdt="1:"+S1+", 2:"+S2+"";break;
    case 3:
      Sdt="1:"+S1+", 2:"+S2+", 3:"+S3+"";break;  
    case 4:
      Sdt="1:"+S1+", 2:"+S2+", 3:"+S3+", 4:"+S4+"";break;
    case 5:
      Sdt="1:"+S1+", 2:"+S2+", 3:"+S3+", 4:"+S4+", 5:"+S5+"";break;
    case 6:
      Sdt="1:"+S1+", 2:"+S2+", 3:"+S3+", 4:"+S4+", 5:"+S5+", 6:"+S6+"";break;
    case 7:
      Sdt="1:"+S1+", 2:"+S2+", 3:"+S3+", 4:"+S4+", 5:"+S5+", 6:"+S6+", 7:"+S7+"";break;
    case 6:
      Sdt="1:"+S1+", 2:"+S2+", 3:"+S3+", 4:"+S4+", 5:"+S5+", 6:"+S6+", 7:"+S7+", 8:"+S8+"";break;
    case 6:
      Sdt="1:"+S1+", 2:"+S2+", 3:"+S3+", 4:"+S4+", 5:"+S5+", 6:"+S6+", 7:"+S7+", 8:"+S8+", 9:"+S9+"";break;
  }
  return Sdt;
}

