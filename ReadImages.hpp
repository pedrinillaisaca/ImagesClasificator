
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <fstream> // Tiene dos clases una para leer archivos ifstream y otra para escribir archivos que es ofstream
#include <sstream>

// Las librerias de C puro acaban en .h (cabeceras)
#include <dirent.h>
#include <cstdlib> 
#include <string>
#include <filesystem>
#include <list>
#include <map>


// Cuando se carga la cabecer opencv.hpp automáticamente se cargan las demás cabeceras
//#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp> // Contiene los elementos básicos como el objeto Mat (matriz que representa la imagen)
#include <opencv2/highgui/highgui.hpp> // Contiene los elementos para crear una interfaz gráfica básica
// OpenCV no está pensado para crear interfaces gráficas potentes. Se centra en la visión artificial y PDI. Si se desea crear una interfaz gráfica completa, se debe usar QT

#include <opencv2/imgcodecs/imgcodecs.hpp> // Contiene las funcionalidad para acceder a los códecs que permiten leer diferentes formatos de imagen (JPEG, JPEG-2000, PNG, TIFF, GIF, etc.)

// Librerías para acceder al video y para poder escribir vídeos en disco
#include <opencv2/video/video.hpp> 
#include <opencv2/videoio/videoio.hpp>

#include <opencv2/imgproc/imgproc.hpp> // Librería para realizar operaciones de PDI 

using namespace std;
using namespace cv;


class Compare{
    private:     
        map<string, map<string, list<string> > > generalMap;
        vector<string> listaImagenes;   
        vector<string> rangos;//variable para almacernar los rangos de las imagenes test pertenecientes a cada una de las 3 clases(clusters)   
        vector<string> testGlobal;//variable que contrendra los directorios de todas las imagenes de test independiente de las clases                
    public:
        Compare();        
        void viewGeneralMap(map<string, map<string, list<string> > > generalMap);
        map<string,double> distanciasGeneralesBGR(map<string, map<string, list<string> > > generalMap);
        double media(map< string , list<string> > mapa);//metodo que devolvera los promedios totales
        double calcularDistancia(vector<Mat> canales_Test,vector<Mat> canales_Train);
        double calcDistForCanal(Mat canales_Test,Mat canales_Train );
        bool compararAllTrain(vector<Mat>,map< string, list<string> >,map<string,double>,string);//calcula aciertos   
        map<string,bool> aciertosFallosBGR(map<string, map<string, list<string> > > nuevoMapa, map< string , double > distanciasGenerales);
        map<string, map<string, list<string> > > transFormar(map<string, map<string, list<string> > > generalMap);
        vector<Mat> calcularHistBGR(string);
        vector<Mat> calcularHistBGR2(string);
        vector<Mat> calcularHistHSV(string);
        bool verificarClase(double distancia,string clase1,map<string,double> distanciasGeneralesBGR);
        // La clase vector es la equivalente del java.util.ArrayList de Java
        //vector<string> split(string, char = ',');
        //bool escribirArchivo(vector<string>, string = "datos.txt");
};

class CompareHSV{
    private:     
        map<string, map<string, list<string> > > generalMap;
        vector<string> listaImagenes;   
        vector<string> rangos;//variable para almacernar los rangos de las imagenes test pertenecientes a cada una de las 3 clases(clusters)   
        vector<string> testGlobal;//variable que contrendra los directorios de todas las imagenes de test independiente de las clases                
    public:
        CompareHSV();        
        void viewGeneralMap(map<string, map<string, list<string> > > generalMap);
        map<string,double> distanciasGeneralesBGR(map<string, map<string, list<string> > > generalMap);
        double media(map< string , list<string> > mapa);//metodo que devolvera los promedios totales
        double calcularDistancia(vector<Mat> canales_Test,vector<Mat> canales_Train);
        double calcDistForCanal(Mat canales_Test,Mat canales_Train );
        bool compararAllTrain(vector<Mat>,map< string, list<string> >,map<string,double>,string);//calcula aciertos   
        map<string,bool> aciertosFallosBGR(map<string, map<string, list<string> > > nuevoMapa, map< string , double > distanciasGenerales);
        map<string, map<string, list<string> > > transFormar(map<string, map<string, list<string> > > generalMap);
        vector<Mat> calcularHistBGR(string);
        vector<Mat> calcularHistBGR2(string);
        vector<Mat> calcularHistHSV(string);
        bool verificarClase(double distancia,string clase1,map<string,double> distanciasGeneralesBGR);
        // La clase vector es la equivalente del java.util.ArrayList de Java
        //vector<string> split(string, char = ',');
        //bool escribirArchivo(vector<string>, string = "datos.txt");
};

class CompareYCrCb{
    private:     
        map<string, map<string, list<string> > > generalMap;
        vector<string> listaImagenes;   
        vector<string> rangos;//variable para almacernar los rangos de las imagenes test pertenecientes a cada una de las 3 clases(clusters)   
        vector<string> testGlobal;//variable que contrendra los directorios de todas las imagenes de test independiente de las clases                
    public:
        CompareYCrCb();        
        void viewGeneralMap(map<string, map<string, list<string> > > generalMap);
        map<string,double> distanciasGeneralesBGR(map<string, map<string, list<string> > > generalMap);
        double media(map< string , list<string> > mapa);//metodo que devolvera los promedios totales
        double calcularDistancia(vector<Mat> canales_Test,vector<Mat> canales_Train);
        double calcDistForCanal(Mat canales_Test,Mat canales_Train );
        bool compararAllTrain(vector<Mat>,map< string, list<string> >,map<string,double>,string);//calcula aciertos   
        map<string,bool> aciertosFallosBGR(map<string, map<string, list<string> > > nuevoMapa, map< string , double > distanciasGenerales);
        map<string, map<string, list<string> > > transFormar(map<string, map<string, list<string> > > generalMap);
        vector<Mat> calcularHistBGR(string);
        vector<Mat> calcularHistBGR2(string);
        vector<Mat> calcularHistHSV(string);
        bool verificarClase(double distancia,string clase1,map<string,double> distanciasGeneralesBGR);
        // La clase vector es la equivalente del java.util.ArrayList de Java
        //vector<string> split(string, char = ',');
        //bool escribirArchivo(vector<string>, string = "datos.txt");
};


class Utility {

    private:
        string directorioRoot;
        map<string, list<string>> getImagenes(const string&);
        int calcularSplitting(int);

    public:
        Utility();
        map<string, map<string, list<string>>> getSubdirectorios();

};