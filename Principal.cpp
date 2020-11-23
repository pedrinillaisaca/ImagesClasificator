#include "ReadImages.hpp"

int main(int argc, char *argv[]){
   

    Utility *utility=new Utility();
    map<string,map<string,list<string>>> mapa = utility->getSubdirectorios(); 
    delete utility;


    Compare *c=new Compare();
    //c->viewGeneralMap(mapa);      
  /**/
    map<string,map<string,list<string>>> nuevoMapa = c->transFormar(mapa);
    map<string,double> distGeneralesBGR =c->distanciasGeneralesBGR(mapa);
   
    map< string, bool > aciertosFallosBGR=c->aciertosFallosBGR(nuevoMapa,distGeneralesBGR);
    double aciertosBGR=0.0;
    for(const auto& index : aciertosFallosBGR) {
        aciertosBGR+=(index.second==1)? 1.0:0.0;
        //cout<<index.first<<" --> "<<index.second<<endl;
    }  
    cout<< "PrecisionBGR: " << aciertosBGR/aciertosFallosBGR.size()<<endl;
    delete c;
/* */  
    // PROCESO CON ESPACIO DE COLOR HSV 
    cout<< "PROCESO CON ESPACIO DE COLOR HSV" <<endl;
    
    CompareHSV *cH=new CompareHSV();
    //c->viewGeneralMap(mapa);      
    //map<string,map<string,list<string>>> nuevoMapa = c->transFormar(mapa);
    map<string,double> distGeneralesHSV =cH->distanciasGeneralesBGR(mapa);
    
    map< string, bool > aciertosFallosHSV=cH->aciertosFallosBGR(nuevoMapa,distGeneralesHSV);
    double aciertosHSV=0.0;
    for(const auto& index : aciertosFallosHSV) {
        aciertosHSV+=(index.second==1)? 1.0:0.0;
        //cout<<index.first<<" --> "<<index.second<<endl;
    } 
    cout<< "PrecisionHSV: " << aciertosHSV/aciertosFallosHSV.size()<<endl;
    delete cH;  
      
    
    // PROCESO CON ESPACIO DE COLOR YCH 
    cout<< "PROCESO CON ESPACIO DE COLOR YCrCb"  <<endl;

    CompareYCrCb *cY=new CompareYCrCb();
    //c->viewGeneralMap(mapa);      
    //map<string,map<string,list<string>>> nuevoMapa = c->transFormar(mapa);
    map<string,double> distGenerales =cY->distanciasGeneralesBGR(mapa);
    
    map< string, bool > aciertosFallos=cY->aciertosFallosBGR(nuevoMapa,distGenerales);
    double aciertosYCrCb=0.0;
    for(const auto& index : aciertosFallos){
        aciertosYCrCb+=(index.second==1)? 1.0:0.0;
        //cout<<index.first<<" --> "<<index.second<<endl;
    } 
    cout<< "Precision YCrCb: " << aciertosYCrCb/aciertosFallos.size()<<endl;
    delete cY;  

  
    cout<<"FIN PROGRAM.... :)"<<endl;    
    return 0;
   
}