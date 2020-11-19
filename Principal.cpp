#include "ReadImages.hpp"

int main(int argc, char *argv[]){
   

    Utility *utility=new Utility();
    map<string,map<string,list<string>>> mapa = utility->getSubdirectorios(); 
    delete utility;


    Compare *c=new Compare();
    //c->viewGeneralMap(mapa);      
    map<string,map<string,list<string>>> nuevoMapa = c->transFormar(mapa);
    map<string,double> distGeneralesBGR =c->distanciasGeneralesBGR(mapa);
 /**/    
    map< string, bool > aciertosFallosBGR=c->aciertosFallosBGR(nuevoMapa,distGeneralesBGR);
    for(const auto& index : aciertosFallosBGR) {
        cout<<index.first<<" "<<index.second<<endl;
    }  
    delete c;
/* 
    // PROCESO CON ESPACIO DE COLOR HSV 
    cout<< "PROCESO CON ESPACIO DE COLOR HSV" <<endl;
    
    CompareHSV *cH=new CompareHSV();
    //c->viewGeneralMap(mapa);      
    //map<string,map<string,list<string>>> nuevoMapa = c->transFormar(mapa);
    map<string,double> distGeneralesHSV =cH->distanciasGeneralesBGR(mapa);
    
    map< string, bool > aciertosFallosHSV=cH->aciertosFallosBGR(nuevoMapa,distGeneralesHSV);
    for(const auto& index : aciertosFallosHSV) {
        cout<<index.first<<" "<<index.second<<endl;
    } 
    delete cH;  
      
    
    // PROCESO CON ESPACIO DE COLOR YCH 
    cout<< "PROCESO CON ESPACIO DE COLOR YCH"  <<endl;

    CompareYCrCb *cY=new CompareYCrCb();
    //c->viewGeneralMap(mapa);      
    //map<string,map<string,list<string>>> nuevoMapa = c->transFormar(mapa);
    map<string,double> distGenerales =cY->distanciasGeneralesBGR(mapa);
    
    map< string, bool > aciertosFallos=cY->aciertosFallosBGR(nuevoMapa,distGenerales);
    for(const auto& index : aciertosFallos){
        cout<<index.first<<" "<<index.second<<endl;
    } 
    delete cY;  
*/
    
    cout<<"FIN PROGRAM.... :)"<<endl;    
    return 0;
   
}