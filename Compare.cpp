
#include "ReadImages.hpp"

Compare::Compare(){
         
}

void Compare::viewGeneralMap(map<string, map<string, list<string> > > generalMap){
    //map<string, map<string, list<string> > > map ; SOLO PARA PRUEBAS        
    
    for(const auto& index : generalMap) {
        cout << index.first << endl;
        for(const auto& v : index.second) {
            cout << "\t" << v.first << endl;
            for (const auto& test : v.second)
                cout << "\t\t" << test << endl;
        }
    }
    /**/
}

map < string , double > Compare::distanciasGeneralesBGR(map<string, map<string, list<string> > > generalMap){
    
    map< string,double> mapaF;
    for(const auto& index : generalMap) {
        //cout << index.first << endl;
        mapaF[index.first]=this->media(index.second);
    }
    cout<< "distanciasGeneralesBGR OK"<<endl;
    return mapaF;
}

double  Compare::media(map< string , list<string> > mapa){
    list<string> test=mapa["TEST"];
    list<string> train=mapa["TRAIN"];
    list<string>::iterator it = test.begin();
    list<string>::iterator jt = train.begin();
    
    double distancia=0.0;
 
    float rango[] = {0, 256};    
    const float *rangoHistograma = {rango};       
    Mat histoB; // Aquí se guardará el histograma del canal Azul como una matriz de una sola columna y n filas
    Mat histoG;
    Mat histoR;
    int tam = 256;    
    try{
            
            for(size_t i=0;i<test.size();i++){
                vector<Mat> canalesBGR_Test;
                
                advance(it,i);
                //canalesBGR_Test=this->calcularHistBGR(*it);
                Mat imgTest = imread(*it, IMREAD_UNCHANGED);//carga img
                cvtColor(imgTest, imgTest,COLOR_RGB2BGR);  
                                    
                split(imgTest, canalesBGR_Test); 
                calcHist(&canalesBGR_Test[0],1,0,Mat(),histoB,1,&tam,&rangoHistograma,true,false);
                calcHist(&canalesBGR_Test[1],1,0,Mat(),histoG,1,&tam,&rangoHistograma,true,false);
                calcHist(&canalesBGR_Test[2],1,0,Mat(),histoR,1,&tam,&rangoHistograma,true,false);
                        
                for(size_t j=0;j<train.size();j++){
                    vector<Mat> canalesBGR_Train;
                    advance(jt,j);
                    //canalesBGR_Train=this->calcularHistBGR(*jt);
                    Mat imgTrain = imread(*jt, IMREAD_UNCHANGED);//carga img
                    cvtColor(imgTrain, imgTrain,COLOR_RGB2BGR); 
                    
                    split(imgTrain, canalesBGR_Train);
                    calcHist(&canalesBGR_Train[0],1,0,Mat(),histoB,1,&tam,&rangoHistograma,true,false);
                    calcHist(&canalesBGR_Train[1],1,0,Mat(),histoG,1,&tam,&rangoHistograma,true,false);
                    calcHist(&canalesBGR_Train[2],1,0,Mat(),histoR,1,&tam,&rangoHistograma,true,false);  

                    distancia+=this->calcularDistancia(canalesBGR_Test,canalesBGR_Train);
                }            
            } 

        }catch(cv::Exception){//control de error cuando se pasa un dierctorio vacio
            cout<<"ERROR CONTROLADO JEJE"<<endl;
        } 
    cout<< "media OK"<<endl;              
    return distancia/test.size();
}

double Compare::calcularDistancia(vector<Mat> canales_Test,vector<Mat> canales_Train){
    
    double d=0.0;
    for (size_t i=0;i<3;i++){
        d+=this->calcDistForCanal(canales_Test[i],canales_Train[i]);
    }
    //cout<< "calcularDistancia OK"<<endl;
    return d;
}

double Compare::calcDistForCanal(Mat canales_Test,Mat canales_Train ){
    double sum=0;    
    for(size_t i=0;i<canales_Test.rows;i++){
        sum+=pow( (double)canales_Test.at<uchar>(i,0) -   (double)canales_Train.at<uchar>(i,0) , 2 );
        }
    //cout<< "calcularDistanciaCANAL OK"<<endl;        
    return sqrt(sum);
}

map < string , bool > Compare::aciertosFallosBGR(map<string, map<string, list<string> > > nuevoMapa, map< string , double > distanciasGeneralesBGR){    
    map < string , bool > retorno; 
    map<string, list<string> > test=nuevoMapa["TEST"];
    map<string, list<string> > train=nuevoMapa["TRAIN"]; 
    
    list<string> subListTrain; 
    list<string>::iterator it = subListTrain.begin();
    map<string,bool>::iterator it_assert = retorno.begin();
            
    float rango[] = {0, 256};
    const float *rangoHistograma = {rango};       
    Mat histoB; // Aquí se guardará el histograma del canal Azul como una matriz de una sola columna y n filas
    Mat histoG;
    Mat histoR;
    int tam = 256;

    vector<Mat> canalesBGR_Test;
    vector<Mat> canalesBGR_Train;
    
    for(const auto& level1 : test) {
        //cout << level1.first << endl;                
        for(const auto& level2 : level1.second) {            

            canalesBGR_Test=calcularHistBGR(level2);
            /* Mat imgTest = imread(level2, IMREAD_UNCHANGED);//carga img
            cvtColor(imgTest, imgTest,COLOR_RGB2BGR);  
                                
            split(imgTest, canalesBGR_Test); 
            calcHist(&canalesBGR_Test[0],1,0,Mat(),histoB,1,&tam,&rangoHistograma,true,false);
            calcHist(&canalesBGR_Test[1],1,0,Mat(),histoG,1,&tam,&rangoHistograma,true,false);
            calcHist(&canalesBGR_Test[2],1,0,Mat(),histoR,1,&tam,&rangoHistograma,true,false);   */

            /* ESPACIOS */ 
            bool prueba=compararAllTrain(canalesBGR_Test,train,distanciasGeneralesBGR,level1.first);//La imagen test sera comparada con todas las imagenes train
            retorno.insert( it_assert,pair<string,bool >(level2,prueba));//OJO FALTA EL ULTIMO METODO y tambien que valide con los demas train ;
        }
        
    }                      

    return retorno;
}


bool Compare::compararAllTrain(vector<Mat> canalesBGR_Test,map< string, list<string> > train,map<string,double> distanciasGeneralesBGR,string claseTest){
    float distancia=0.0;
    bool fin;
    float rango[] = {0, 256};
    const float *rangoHistograma = {rango};       
    Mat histoB; // Aquí se guardará el histograma del canal Azul como una matriz de una sola columna y n filas
    Mat histoG;
    Mat histoR;
    int tam = 256;

    //vector<Mat> canalesBGR_Test;
    vector<Mat> canalesBGR_Train;

    for(const auto& level1 : train) {
        //cout << level1.first << endl;                
        for(const auto& level2 : level1.second) {            
            Mat imgTest = imread(level2, IMREAD_UNCHANGED);//carga img
            cvtColor(imgTest, imgTest,COLOR_RGB2BGR);  
                                
            split(imgTest, canalesBGR_Train); 
            calcHist(&canalesBGR_Train[0],1,0,Mat(),histoB,1,&tam,&rangoHistograma,true,false);
            calcHist(&canalesBGR_Train[1],1,0,Mat(),histoG,1,&tam,&rangoHistograma,true,false);
            calcHist(&canalesBGR_Train[2],1,0,Mat(),histoR,1,&tam,&rangoHistograma,true,false);  

            distancia+=this->calcularDistancia(canalesBGR_Test,canalesBGR_Train);           
            fin=verificarClase(distancia,claseTest,distanciasGeneralesBGR);
        }
        
    }               

    return fin;
}

bool Compare::verificarClase(double distancia,string claseTest,map<string,double> distanciasGeneralesBGR){
    double aux=99999.0;
    string clase;
    for(const auto& index : distanciasGeneralesBGR) {
        double operacion=index.second-distancia;
        if(operacion<aux){
            aux=operacion;
            clase=index.first;
        }            
    }

    if(clase.compare(claseTest)==0){
        return true;
    }
    return false;
}

vector<Mat> Compare::calcularHistBGR(string img){
    //cout<<img<<endl;
    vector<Mat> canalesBGR; 
    try{

        Mat imagen = imread(img, IMREAD_UNCHANGED);//carga img
        cvtColor(imagen, imagen,COLOR_RGB2BGR);
           
        split(imagen, canalesBGR);        
        float rango[] = {0, 256};
        const float *rangoHistograma = {rango};
        Mat histoB; // Aquí se guardará el histograma del canal Azul como una matriz de una sola columna y n filas
        Mat histoG;
        Mat histoR;
        int tam = 256;
        // Función de OpenCV para calcular el histograma (permite calcular el histograma de un conjunto de imágenes)
        calcHist(&canalesBGR[0],1,0,Mat(),histoB,1,&tam,&rangoHistograma,true,false);
        //calcHist(&canalesBGR[1],1,0,Mat(),histoG,1,&tam,&rangoHistograma,true,false);
        //calcHist(&canalesBGR[2],1,0,Mat(),histoR,1,&tam,&rangoHistograma,true,false);    

    }catch(cv::Exception){//control de error cuando se pasa un dierctorio vacio
        cout<<"ERROR CONTROLADO JEJE"<<endl;
    } 
    
    return canalesBGR;
}


vector<Mat> Compare::calcularHistHSV(string img){//PASAR COMO PARAMETRO LA IMAGEN PARA CONVERTIDA EN EL ESPACIO DE COLOR 
    vector<Mat> canalesHSV;
    try{
        Mat imagen = imread(img, IMREAD_UNCHANGED);//carga img
        cvtColor(imagen, imagen,COLOR_RGB2BGR);
        
        split(imagen, canalesHSV);                        
        
        float rango[] = {0, 256};
        const float *rangoHistograma = {rango};
        Mat histoH; // Aquí se guardará el histograma del canal Azul como una matriz de una sola columna y n filas
        Mat histoS;
        Mat histoV;
        int tam = 256;
        
        calcHist(&canalesHSV[0],1,0,Mat(),histoH,1,&tam,&rangoHistograma,true,false);
        calcHist(&canalesHSV[1],1,0,Mat(),histoS,1,&tam,&rangoHistograma,true,false);
        calcHist(&canalesHSV[2],1,0,Mat(),histoV,1,&tam,&rangoHistograma,true,false);    

    }catch(cv::Exception){//control de error cuando se pasa un dierctorio vacio
            cout<<"ERROR CONTROLADO JEJE"<<endl;
        } 
    
    return canalesHSV;
}

map<string, map<string, list<string> > > Compare::transFormar(map<string, map<string, list<string> > > generalMap){
    map< string, map< string, list<string> > > nuevoMapa;
    map< string, list<string> > subMapaTest;
    map< string, list<string> > subMapaTrain;
    list< string > subListTest;
    list< string > subListTrain;

    map<string,list<string>>::iterator it_subMTest = subMapaTest.begin();
    map<string,list<string>>::iterator it_subMTrain = subMapaTrain.begin();
    map< string, map< string, list<string> > >::iterator it_nuevoMapa = nuevoMapa.begin();

    for(const auto& level1 : generalMap) {
               
        for(const auto& level2 : level1.second) {
            //cout << "\t" << level2.first << endl;
            for (const auto& level3 : level2.second){

                if(level2.first.compare("TEST")==0){                
                   subListTest.emplace_back(level3);

                }else{
                    subListTrain.emplace_back(level3);                
                }
            }
        } 
        subMapaTest.insert( it_subMTest,pair<string,list<string> >(level1.first,subListTest));
        subMapaTrain.insert( it_subMTrain,pair< string,list<string> > (level1.first,subListTrain));
        subListTest.clear();
        subListTrain.clear();
    }


    nuevoMapa.insert( it_nuevoMapa, pair<string, map< string, list<string> >> ("TEST",subMapaTest));
    nuevoMapa.insert( it_nuevoMapa, pair<string, map< string, list<string> >> ("TRAIN",subMapaTrain));

    //map<string, map<string, list<string> > > map ; SOLO PARA PRUEBAS        
    
    /* for(const auto& level1 : nuevoMapa) {
        cout << level1.first << endl;
        for(const auto& level2 : level1.second) {
            cout << "\t" << level2.first << endl;
            for (const auto& level3 : level2.second)
                cout << "\t\t" << level3 << endl;
        }
    }
 */
    return nuevoMapa;
}

