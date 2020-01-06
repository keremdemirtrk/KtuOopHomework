// Writed by Kerem Demirtürk 348367

#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
struct rgb{  //Image sınıfının rgb struct'ı oluşturuldu.
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    void operator=(int a){
        red = a;
        green = a;
        blue = a;
    }
};

//Matrix Class'ı oluşturuldu.
template <typename T> 
class Matrix{
protected: 
    vector< vector<T> > matris;
public: 
    Matrix();
    Matrix(int width, int height, T value);
    Matrix(int width, int height, char type);
    void print();
    void print(string fileName);
    void resize(int newWidth, int newHeight);
    void t();
    Matrix<T> inv();
    double det();
    void emul(Matrix<T> const& m2);
    Matrix<T>* operator+(Matrix<T> const& m2);
    Matrix<T>* operator-(Matrix<T> const& m2);
    Matrix<T>* operator*(Matrix<T> const& m2);
    void operator = (Matrix <T> const& m2);
    Matrix<T>* operator+(T const& value);
    Matrix<T>* operator-(T const& value);
    Matrix<T>* operator*(T const& value);
    Matrix<T>* operator/(T const& value);
    Matrix<T>* operator%(T const& value);
    Matrix<T>* operator^(T const& value);

};

//Matrix sınıfından kalıtılmış Image sınıfı oluşturuldu.
template <typename T>
class Image : public Matrix<rgb>{
    char header[54];
    bool binary = false;
public:
    Image();
    Image(int width,int height);
    Image(string filename,string format);
    void print();
    void imread(string filename,string format);
    void color2gray();
    void imwrite(string filename, string format);
    void gray2binary(int thr);
    void erosion();
    void dilation();
    void opening();
    void closing();


};

//Matrix sınıfından kalıtılmış Table sınıfı oluşturuldu.
template <typename T>
class Table : public Matrix<T>{
private:
    vector<string> rownames;
    vector<string> colnames;
public:
    Table();
    Table(int r, int c, int d);
    Table(int r, int c, char ch);
    T itemAt(int r, int c);
    T itemAt(string s);
    T itemAt(string rs, string cs);
    void setRowNames(string s[], int n);
    void setColNames(string s[], int n);
    void print();

    void setDefaultValues();
};

//Default constructor oluşturuldu.
template <typename T> 
Matrix<T>::Matrix(){
    int w=10, h=10;
    matris.resize(h);
    for(int i=0; i<h; i++){
        matris[i].resize(w);
        for(int j=0; j<w; j++){
            matris[i][j] = 0;
        }
    }
}

// 2. Constructor oluşturuldu.
template <typename T> 
Matrix<T>::Matrix(int width, int height, T value){
    value = rand()%15;
    int w=width, h=height;
    matris.resize(h);
    for(int i=0; i<h; i++){
        matris[i].resize(w);
        for(int j=0; j<w; j++){
            matris[i][j] = value;
        }
    }
}

//3. Constructor oluşturuldu.
template <typename T> 
Matrix<T>::Matrix(int width, int height, char type){
    int w=width, h=height;
    matris.resize(h);
    for(int i=0; i<h; i++){
        matris[i].resize(w);
        for(int j=0; j<w; j++){
            matris[i][j] = 0;
        }
    }

    
    // Birim matris
    if( type == 'e'){
        if( width == height){
            for(int size=0; size < matris.size(); size++){
                matris[size][size] = 1;
            }
        }
    }
    // Rastgele matris 
    else if( type == 'r'){
        for(int i=0; i<h; i++){
            matris[i].resize(w);
            for(int j=0; j<w; j++){
                matris[i][j] = rand()%256;
            }
        }
    }
}

// + Operator Overloading
template <typename T> 
Matrix<T>* Matrix<T>::operator+(Matrix<T> const& m2){
    if(this->matris.size() == m2.matris.size()){
        for(int i=0;i<matris.size();i++){
            for(int j=0;j<matris[0].size();j++){
                this->matris[i][j] += m2.matris[i][j];
            }
        }
    }else{
        cout<<"matrisiniz uyumsuz:"<<endl;
    }
    
    return this;
}

// - Operator Overloading
template <typename T>
Matrix<T>* Matrix<T>::operator-(Matrix<T> const& m2){
    if(this->matris.size() == m2.matris.size()){
        for(int i=0;i<matris.size();i++){
            for(int j=0;j<matris[0].size();j++){
                this->matris[i][j] -= m2.matris[i][j];
            }
        }
    }
    else{
        cout<<"matrisiniz uyumsuz:"<<endl;
    }
    return this;
}

// * Operator Overloading
template <typename T>
Matrix<T>* Matrix<T>::operator*(Matrix<T> const& m2){
    if(this->matris.size() == m2.matris.size()){
        Matrix<T> *newMat = new Matrix<T>(matris.size(), m2.matris[0].size(), (T) 0);
        for(int i=0;i<matris.size();i++){
            for(int j=0;j<m2[0].size();j++){
                for(int k=0;k<matris[0].size;k++){
                    newMat->matris[i][j] = newMat->matris[i][j] + (matris[i][k] * m2.matris[k][j]);
                }
            }
        }
        return newMat;
    }
    else{
        cout<<"matrisiniz uyumsuz:"<<endl;
    }
    return this;
}

//  Operator Overloading
template <typename T>
Matrix<T>* Matrix<T>::operator+(T const& value){
    cout << "operator+ çalışıyor" <<  endl;
    //matris temp(matris.size());
/*    for(int i=0;i<matris.size();i++){
        this->matris[i][0] = this->matris[i][0] + value;
    }
    cout << "operator+ çalıştı" <<  endl;
    return this;
*/
    for(int i=0; i<matris.size(); i++){
        for(int j=0; j<matris[0].size(); j++){
            this->matris[i][j] = this->matris[i][j] + value;
        }
    }
    return this;
}

//  Operator Overloading
template <typename T>
Matrix<T>* Matrix<T>::operator-(T const& value){
    for(int i=0; i<matris.size(); i++){
        for(int j=0; j<matris[0].size(); j++){
            this->matris[i][j] = this->matris[i][j] - value;
        }
    }
    return this;
}

// * Operator Overloading
template <typename T>
Matrix<T>* Matrix <T>::operator*(T const& value){
    for(int i=0; i<matris.size(); i++){
        for(int j=0; j<matris[0].size(); j++){
            this->matris[i][j] = this->matris[i][j] * value;
        }
    }
    return this;

}

template <typename T>
void Matrix <t>::operator=(Matrix <T> const& m2){
    for(int i=0;i<matris.size();i++){
        for(int j=0;j<matris[0].size();j++){
            this->matris[i][j] = m2.matris[i][j];
        }
    }
    return this;
}


//  Operator Overloading
template <typename T>
Matrix<T>* Matrix <T>::operator/(T const& value){
    for(int i=0; i<matris.size(); i++){
        for(int j=0; j<matris[0].size(); j++){
            this->matris[i][j] = this->matris[i][j] / value;
        }
    }
    return this;
}

//  Operator Overloading
template <typename T>
Matrix<T>* Matrix <T>::operator%(T const& value){
    for(int i=0; i<matris.size(); i++){
        for(int j=0; j<matris[0].size(); j++){
            this->matris[i][j] = this->matris[i][j] % value;
        }
    }
    return this;
}

//  Operator Overloading
template <typename T>
Matrix<T>* Matrix <T>::operator^(T const& value){
    for(int i=0; i<matris.size(); i++){
        for(int j=0; j<matris[0].size(); j++){
            this->matris[i][j] = this->matris[i][j] ^ value;
        }
    }
    return this;
}

//Print fonksiyonu
template <typename T> 
void Matrix<T>::print(){
    for(int h=0; h<matris.size(); h++){
        for(int w=0; w<matris[0].size(); w++){
            cout<< " "<< matris[h][w];
        }
        cout << endl;
    }
	cout << endl;
}

//Dosyayı okuma
template <typename T> 
void Matrix<T>::print(string fileName){
    ofstream myFile;
    myFile.open(fileName);

    for(int h=0; h<matris.size(); h++){
        for(int w=0; w<matris[0].size(); w++){
            myFile << matris[h][w]<<" ";
        }
        myFile << endl; 
    }
}

//Yeniden Boyutlandırma
template <typename T>
void Matrix<T>::resize(int newWidth, int newHeight){
    matris.resize(newHeight);
    for(int i=0; i<newHeight; i++){
        matris[i].resize(newWidth);
    }
}

//Transpoze
template <typename T>
void Matrix<T>::t(){
    vector< vector<T> > tempMatrix;
    // tempMatris boyutlandırıldı
    tempMatrix.resize(this->matris[0].size());
    for(int x=0;x<matris[0].size();x++){
        tempMatrix[x].resize(this->matris.size());
    }

    // tempMatris'e atama yapıldı
    for(int i=0; i<matris.size(); i++){
        for(int j=0; j<matris[0].size(); j++){
            tempMatrix[j][i] = this->matris[i][j];
        }
    }

    // this matris boyutlandırıldı
    this->matris.clear();
    this->matris.resize(tempMatrix.size());
    for(int x=0;x<tempMatrix.size();x++){
        this->matris[x].resize(tempMatrix[0].size());
    }

    // this matris'e atama yapıldı
    for(int i=0;i<this->matris.size();i++){
        for(int j=0;j<this->matris[0].size();j++){
            this->matris[i][j] = tempMatrix[i][j];
        }
    }
}

//Ters
template<typename T>
Matrix<T> Matrix<T>::inv(){
	Matrix<T> temp;
	temp.resize(2,2);
	temp.matris[0][0] = this->matris[1][1];
	temp.matris[1][1] = this->matris[0][0];
	temp.matris[0][1] = this->matris[0][1] * -1;
	temp.matris[1][0] = this->matris[1][0] * -1;

	temp * (1/this->det());
	return temp;

}

//Determinant
template <typename T>
double Matrix<T>::det(){
	return this->matris[0][0] * this->matris[1][1] - this->matris[0][1]*this->matris[1][0];
}

//Eleman Düzeyinde Çarpma
template <typename T>
void Matrix<T>::emul(Matrix<T> const& matrix2){
    for(int i=0; i<matris.size(); i++){
        for(int j=0; j<matris[0].size(); j++){
            this->matris[i][j] = this->matris[i][j] * matrix2.matris[i][j];
        }
    }
    return this;
}

//Default Constructor
template < >
Image<rgb>::Image(){
    int w=255,h=255;
    matris.resize(h);
    for(int x=0;x<w;x++){
        matris.resize(w);
        for(int j=0;j<h;j++){
            matris[x][j].red = 0;
            matris[x][j].green = 0;
            matris[x][j].blue = 0;
        }
    }
}
//2. Constructor
template < >
Image<rgb>::Image(int width,int height){
    int w=width,h=height;
    matris.resize(h);
    for(int x=0;x<w;x++){
        matris.resize(w);
        for(int j=0;j<h;j++){
            matris[x][j].red = 0;
            matris[x][j].green = 0;
            matris[x][j].blue = 0;
        }
    }
}

template <> 
void Image<rgb>::print(){
    for(int h=0; h<matris.size(); h++){
        for(int w=0; w<matris[0].size(); w++){
            //cout << (int)matris[h][w].red << matris[h][w].green << matris[h][w].blue;
        }
        cout << endl;
    }
}

//Dosyadan Okuma


//Dosyaya yazma
template < >
void Image<rgb>::imwrite(string filename, string format){
    ofstream file;
    file.open(filename+"."+format, ofstream::binary);
    if(format == "bin"){
        file.put((unsigned char)matris.size());
        file.put((unsigned char)matris[0].size());

        for(int i=0;i<matris.size();i++){
            for(int j=0;j<matris[0].size();j++){
                file.put(matris[i][j].red);
                file.put(matris[i][j].green);
                file.put(matris[i][j].blue);
            }
        }
    }else if(format == "bmp"){
        cout << "dosya formatı BMP WRITE MODE" << endl;
        unsigned int width, height;
        file.write(header, 54);
        width = *(int*)&header[18];
        height = *(int*)&header[22];
        file.seekp(54);
        matris.resize(height);
        for(int x=0;x<width;x++){
            matris.resize(width);
        }
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                char r, g, b;
                r = matris[i][j].red;
                g = matris[i][j].green;
                b = matris[i][j].blue;
                file.put(r); 
                if(binary == true){
                    if(g == 1){
                        g = 255;
                    }
                }
                file.put(g); 
                file.put(b); 
            }
        }
    }
    file.close();
}

//Okuma İşlemi
template < >
void Image<rgb>::imread(string filename,string format){
    ifstream file;
    file.open(filename+"."+format, ifstream::binary);
    
    if(format == "bin"){
        cout << "dosya formatı BIN" << endl;
        unsigned char w, h;
        file >> w;
        file >> h;
        cout << "w:" << w << " h:" << h << endl;
        this.resize(w,h);

        for(int i=0; i<matris.size(); i++){
            for(int j=0; j<matris[0].size(); j++){
                char r, g, b;
                file.get(r);
                file.get(g);
                file.get(b);
                matris[i][j].red = r; 
                matris[i][j].green = g; 
                matris[i][j].blue = b; 
            }
        }
    }else if(format == "bmp"){
        cout << "dosya formatı BMP" << endl;
        unsigned int w, h;
        file.read(header, 54);
        w = *(int*)&header[18];
        h = *(int*)&header[22];
        cout << "w:" << w << " h:" << h << endl;
        matris.resize(h);
        file.seekg(54);
        for(int x=0;x<w;x++){
            matris[x].resize(w);
        }
        for(int i=0; i<matris.size(); i++){
            for(int j=0; j<matris[0].size(); j++){
                char r, g, b;
                file.get(r);
                file.get(g);
                file.get(b);
                matris[i][j].red = r; 
                matris[i][j].green = g; 
                matris[i][j].blue = b; 
            }
        }
    }
    file.close();
}

template < >
Image<rgb>::Image(string filename, string format){
    imread(filename,format);
}

//r ve b sıfır g 1 kalıcak.
template < >
void Image<rgb>::color2gray(){
    for(int i=0;i<matris.size();i++){
        for(int j=0;j<matris[0].size();j++){
            matris[i][j].red = 0;
            matris[i][j].blue = 0;
        }
    }
}

template < >
void Image<rgb>::erosion(){
    vector <vector<int> > tempmatris;
    tempmatris.resize(matris.size());
    for(int x=0;x<matris.size();x++){
        tempmatris[x].resize(matris[0].size());
    }
    for(int i=0;i<tempmatris.size();i++){
        for(int j=0;j<tempmatris[0].size();j++){
            tempmatris[i][j] = 1;
        }
    }

    for(int i=1;i<matris.size()-1;i++){
        for(int j=1;j<matris[0].size()-1;j++){
            if(matris[i+1][j].green == 0)
                tempmatris[i][j] = 0;
            if(matris[i+1][j+1].green == 0)
                tempmatris[i][j] = 0;
            if(matris[i][j+1].green == 0)
                tempmatris[i][j] = 0;
            if(matris[i-1][j].green == 0)
                tempmatris[i][j] = 0;
            if(matris[i-1][j-1].green == 0)
                tempmatris[i][j] = 0;
            if(matris[i][j-1].green == 0)
                tempmatris[i][j] = 0;
            if(matris[i+1][j-1].green == 0)
                tempmatris[i][j] = 0;
            if(matris[i-1][j+1].green == 0)
                tempmatris[i][j] = 0; 
        }
    }
    for(int x=0;x<matris.size();x++){
        for(int j=0;j<matris[0].size();j++){
            matris[x][j] = tempmatris[x][j];
        }
    }
}
template < >
void Image<rgb>::dilation(){
    vector <vector<int> > tempmatris;
    tempmatris.resize(matris.size());
    for(int x=0;x<matris.size();x++){
        tempmatris[x].resize(matris[0].size());
    }

    for(int i=1;i<matris.size()-1;i++){
        for(int j=1;j<matris[0].size()-1;j++){
            if(matris[i+1][j].green == 1)
                tempmatris[i][j] = 1;
            if(matris[i+1][j+1].green == 1)
                tempmatris[i][j] = 1;
            if(matris[i][j+1].green == 1)
                tempmatris[i][j] = 1;
            if(matris[i-1][j].green == 1)
                tempmatris[i][j] = 1;
            if(matris[i-1][j-1].green == 1)
                tempmatris[i][j] = 1;
            if(matris[i][j-1].green == 1)
                tempmatris[i][j] = 1;
            if(matris[i+1][j-1].green == 1)
                tempmatris[i][j] = 1;
            if(matris[i-1][j+1].green == 1)
                tempmatris[i][j] = 1; 
        }
    }
    for(int x=0;x<matris.size();x++){
        for(int j=0;j<matris[0].size();j++){
            matris[x][j] = tempmatris[x][j];
        }
    }
}

template < >
void Image<rgb>::opening(){
    dilation();
    erosion();
}

template < >
void Image<rgb>::closing(){
    erosion();
    dilation();
}




template < >
void Image<rgb>::gray2binary(int thr){
    binary = true;
    for(int i=0;i<matris.size();i++){
        for(int j=0;j<matris[0].size();j++){
            if(matris[i][j].green>thr){
                matris[i][j].green = 1;
            }else{
                matris[i][j].green = 0;
            }
        }
    }
}





template <typename T>
Table<T>::Table(){

        cout<< "Default constructor çalıştı." <<endl;

    int w=10, h=10;
    this->matris.resize(h);
    for(int i=0;i<h;i++){
        this->matris[i].resize(w);
        for(int j=0;j<w;j++){
            this->matris[i][j] = 0;
        }
    }

    rownames.resize(w);
    colnames.resize(h);
    setDefaultValues();

}

//Constructor
template <typename T>
Table<T>::Table(int r, int c, int d)
{
    int w=r, h=c;
    this->matris.resize(h);
    for(int i=0;i<h;i++){
        this->matris[i].resize(w);
        for(int j=0;j<w;j++){
            this->matris[i][j] = d;
        }
    }

    rownames.resize(w);
    colnames.resize(h);
    setDefaultValues();

}

//Constructor
template <typename T>
Table<T>::Table(int r, int c, char ch)
{
    int w=c, h=r;
    this->matris.resize(h);
    for(int i=0;i<h;i++){
        this->matris[i].resize(w);
        for(int j=0;j<w;j++){
            if (ch != 'r') {
                this->matris[i][j] = 0;
            } else 
            {
                this->matris[i][j] = rand()%256;
            }
        }
    }

    rownames.resize(w);
    colnames.resize(h);
    setDefaultValues();
}

//Setter
template <typename T>
void Table<T>::setDefaultValues()
{
	char kr1 = 'A';
	char kr2 = 'A';
    // setting default colnames
	colnames.resize(this->matris[0].size());
    for (int i = 0; i<this->matris[0].size(); i++)
    {	
        this->colnames[i].push_back(kr1);
        this->colnames[i].push_back(kr2);
		if(kr2 == 'Z'){
			kr1++;
			kr2 = 'A';
			continue;
		}
		kr2++;
    }

    // setting default rownames
    for (int i = 1; i<=this->matris[0].size(); i++)
    {
        this->rownames[i - 1] = to_string(i);
    }
}

//Fonksiyonlar
template <typename T>
T Table<T>::itemAt(int r, int c)
{
    return this->matris[r][c];
}

template <typename T>
T Table<T>::itemAt(string s)
{
	// Önce kolon adı, sonra satır adı
	// AASatir1, AA10, DC99
	string colName;
	colName.push_back(s[0]);
	colName.push_back(s[1]);

	string rowName;
	for(int i=2; i<s.size(); i++){
		rowName.push_back(s[i]);
	}
	return this->itemAt(rowName, colName);
}

template <typename T>
T Table<T>::itemAt(string rs, string cs)
{
	int x, y;
	bool foundr = false;
	bool foundc = false;
	for(x=0; x<this->rownames.size(); x++){
		if(rs == this->rownames[x]){
			foundr = true;
			break;
		} 
	}

	for(y=0; y<this->colnames.size(); y++){
		if(cs == this->colnames[y]){
			foundc = true;
			break;
		} 
	}
	if(foundr && foundc){
    	return this->matris[x][y];
	}else{
		return 0;
	}
}

template <typename T>
void Table<T>::setRowNames(string s[], int n)
{
    for(int i=0; i<n; i++)
    {
        if (s[i].size() > 8) {
            cout << s[i] << " 8 karakterden büyük" << endl;
			continue;
        }
        rownames[i] = s[i];
    }
}

template <typename T>
void Table<T>::setColNames(string s[], int n)
{
    for(int i=0; i<n; i++)
    {
        if (s[i].size() > 4) {
            cout << s[i] << " 4 karakterden büyük" << endl;
			continue;
        }
        colnames[i] = s[i];
    }
}

template <typename T>
void Table<T>::print(){
	cout << "         ";
	for(int i=0; i<colnames.size(); i++){
		cout << setw(5) << right << colnames[i];
	}
	cout << endl;

	for(int i=0; i<this->matris.size(); i++){
		cout << setw(9) << right << rownames[i];
		for(int j=0; j<this->matris[0].size(); j++){
			cout << setw(5) << right << this->matris[i][j];
		}
		cout << endl;
	}
}


int main(){
    srand(time(NULL));
    Matrix <int> *m1 = new Matrix <int>();
    Matrix <int> *m2 = new Matrix <int>(2,2,'r');
    //Matrix <int> *m3 = new Matrix <int>(5,5,'e');
    //Matrix <int> *m4 = new Matrix <int>(3,5,'r');
    //m1->print();

    //Table<int> t1(10,10,'r');

    //string str[] = {"Satir 121", "Satir 2", "Satir 3","Satir 4"};
	//t1.setRowNames(str, 4);
	//t1.print();

	//cout << t1.itemAt("AASatir 2") << endl;


   // Table <int> *a1 = new Table <int>(6,6,4);
   // a1->print();
   // cout << endl;
   // a1->itemAt(5, 3); cout <<endl;
   // a1->itemAt("A2"); cout <<endl;
   // a1->itemAt("1", "A"); cout <<endl;

   // m2 = *m2 * 4;
     m2->print();
     m2 = *m1 + *m2;
     m2->print();


    //m1->print();
   // Image<rgb> im("lenna","bmp");
   // im.color2gray();
   // im.gray2binary(100);
   // im.imwrite("lennaporn","bmp");
   // im.erosion();
   // im.imwrite("lenna2","bmp");
   // im.dilation();
   // im.imwrite("lenna3","bmp");

    //im = im+im;

   // im.print();
     //cout << "test";
//    m4->print();
  //  m4->t();
    //m4->print();
    // m3->print();
    // m4->print();

   // m2->resize(5,5);
   // m2->print();
   // m2->print("file.txt");
    return 0;
}
