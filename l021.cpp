//
// Created by Nithya Chintalapati on 10/5/20.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ios>
#include <cmath>


bool isInside(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

void part2();

void bresenham(int d, int d1, int d2, int d3);

double getSlope(double y1, double y2, double x1, double x2);

double getDistance(double i, double i1, double i2, double i3);

void drawPerpendicularLine(double bx, double by, double slope, double distance);

using namespace std;
int matrix[800][800];
int Ecoords[2];


int main() {
    std::ofstream myfile;
    myfile.open ("points.txt");
    ofstream test;
    test.open ("test.ppm");
    test << "P3" << endl << 800 << ' ' << 800 << endl << "1" << endl;


    srand( time(NULL) );


//    double x1 = ((double) rand() / (RAND_MAX));
//    double y1 = ((double) rand() / (RAND_MAX));
//
//    double x2 = ((double) rand() / (RAND_MAX));
//    double y2 = ((double) rand() / (RAND_MAX));
//
//    double x3 = ((double) rand() / (RAND_MAX));
//    double y3 = ((double) rand() / (RAND_MAX));
//
//    double x4 = ((double) rand() / (RAND_MAX));
//    double y4 = ((double) rand() / (RAND_MAX));

    double x1 = 0.12596813455501951;
    double y1 = 0.14643746621275203;

    double x2 = 0.17449463772331114;
    double y2 = 0.73137621569045641;

    double x3 = 0.24005710950123943;
    double y3 = 0.63983938733108314;

    double x4 = 0.78058287351419353;
    double y4 = 0.25635515305043904;

    for (int n = 0; n < 800; ++n) {
        for (int m = 0; m < 800; ++m) {
            matrix[n][m] = 0;
        }
    }

    bool check4 = isInside(x1, y1, x2, y2, x3,y3, x4, y4);
    bool check1 = isInside(x4, y4, x2, y2, x3,y3, x1, y1);
    bool check2 = isInside(x1, y1, x4, y4, x3,y3, x2, y2);
    bool check3 = isInside(x1, y1, x2, y2, x4,y4, x3, y3);

//    cout << "check 1: " << check1 << "\n";
//    cout << "check 2: " << check2 << "\n";
//    cout << "check 3: " << check3 << "\n";
//    cout << "check 4: " << check4 << "\n";


    while(check4 || check3 || check2 || check1)
    {
//         x4 = ((double) rand() / (RAND_MAX));
//         y4 = ((double) rand() / (RAND_MAX));
        x4 = 0.23475678601989372;
        y4 = 0.55730263635390564;

         check4 = isInside(x1, y1, x2, y2, x3,y3, x4, y4);
         check1 = isInside(x4, y4, x2, y2, x3,y3, x1, y1);
         check2 = isInside(x1, y1, x4, y4, x3,y3, x2, y2);
         check3 = isInside(x1, y1, x2, y2, x4,y4, x3, y3);

         cout << "inside" << "\n";

    }


    myfile << "(" <<std::setprecision(17)<< x1 << "," << y1 << ") , ";
    myfile << "(" <<std::setprecision(17)<< x2 << "," << y2 << ") , ";
    myfile << "(" <<std::setprecision(17)<< x3 << "," << y3 << ") , ";
    myfile << "(" <<std::setprecision(17)<< x4 << "," << y4 << ")";
    myfile.close();


    part2();

    for (int n = 0; n < 800; ++n) {
        for (int m = 0; m < 800; ++m) {

            test<< matrix[n][m] << " "<< matrix[n][m] << " " << matrix[n][m] << "     ";          //std::to_string(matrix[n][m]) << " ";

        }
        test << endl;
    }


    test.close();



    //myfile.close();
    return 0;
}

float getArea(double x1, double y1, double x2, double y2, double x3, double y3)
{
    return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}

bool isInside(double x1, double y1, double x2, double y2, double x3, double y3, double x, double y) {
    double A = getArea (x1, y1, x2, y2, x3, y3);
    string Asub = to_string(A);
    Asub.substr(0,5);

    A = stod(Asub);
    //cout << "A: " << A << "  ";
            /* Calculate area of triangle PBC */
    double A1 = getArea (x, y, x2, y2, x3, y3);
    /* Calculate area of triangle PAC */
    double A2 = getArea (x1, y1, x, y, x3, y3);

    /* Calculate area of triangle PAB */
    double A3 = getArea (x1, y1, x2, y2, x, y);

    double sum = A1 + A2 + A3;

    string sumsub = to_string(sum);
    sumsub.substr(0,5);

    sum = stod(sumsub);
    //out << "Sum: " << sum << "\n";



    /* Check if sum of A1, A2 and A3 is same as A */

    return (A == sum);
}


void part2() {
    int points[8];
    std::ifstream file("points.txt");
    std::string str;
    while (std::getline(file, str)) {
        std::cout << str << "\n";
    }

    string getx1 = str.substr(1,19);
    double x1 = stold(getx1);
    points[0]= (int)(800*x1);

    string gety1 = str.substr(21,19);
    double y1 = stold(gety1);
    points[1]= (int)(800*y1);

    string getx2 = str.substr(45,19);
    double x2 = stold(getx2);
    points[2]= (int)(800*x2);

    string gety2 = str.substr(65,19);
    double y2 = stold(gety2);
    points[3]= (int)(800*y2);

    string getx3 = str.substr(89,19);
    double x3 = stold(getx3);
    points[4]= (int)(800*x3);

    string gety3 = str.substr(109,19);
    double y3 = stold(gety3);
    points[5]= (int)(800*y3);

    string getx4 = str.substr(133,19);
    double x4 = stold(getx4);
    points[6]= (int)(800*x4);

    string gety4 = str.substr(153,19);
    double y4 = stold(gety4);
    points[7]= (int)(800*y4);

    cout << points[0]<< "  " << points[1] <<"\n"; //A
    cout << points[2]<< "  "  << points[3] <<"\n"; //B
    cout << points[4]<< "  " << points[5]<<"\n"; //C
    cout << points[6]<< "  " << points[7] <<"\n"; //D
    file.close();

    matrix[points[1]][points[0]] = 1;
    matrix[points[3]][points[2]] = 1;
    matrix[points[5]][points[4]] = 1;
    matrix[points[7]][points[6]] = 1;
    bresenham(points[0], points[1], points[4], points[5]);

    double perpSlope = (double)-1 / (double)getSlope(y3,y1,x3, x1);
    double ac = getDistance(x1, y1, x3, y3);
    drawPerpendicularLine(x4, y4, perpSlope, ac); // DE

    bresenham(Ecoords[0], Ecoords[1], points[2], points[3]); // BE

    int slopeperpc = (double)-1 / (double)getSlope(points[3], Ecoords[1],points[2], Ecoords[0]);
    double bBE = (slopeperpc * -1 * x1) - (-1 * y1);
    double n = x1;
    double ny = (slopeperpc * n) + bBE;
    while( n< 1 &&  0 < n && ny< 1 && 0< ny)
    {
        n = n - 0.000001;
        ny = (slopeperpc * n) + bBE;
    }
    bresenham(x1, y1, n, ny);
    //drawPerpendicularLine(x3, y3, slopeperpc, 0.12);

}

void drawPerpendicularLine(double bx, double by, double slope, double distance) {
    double bBE = (slope * -1 * bx) - (-1 * by); // y = slope * x + bBE
    double distanceCurrent;
        cout << "x4: " << bx << setprecision(17) << "\n";
        cout << "y4: " << by << setprecision(17) << "\n";
        cout << "slope: " << slope << setprecision(17) << "\n";
        cout << "b: " << bBE << setprecision(17) << "\n";
        double ix = bx;
        double iy = (slope * ix) - bBE;
        cout << "distance: " << distance << setprecision(17) << "\n";
        while(distanceCurrent < distance )
        {
//            if(slope > 0)
            ix = ix - 0.00000001;
            iy = (double)(slope * ix) + (double)bBE;
//            if(slope < 0)
//                ix= ix + 0.000001;

            distanceCurrent = (double)getDistance(bx, by, ix, iy);
            //cout << "current: " << distanceCurrent << "\n";
        }
        cout << "iy1: " << iy << setprecision(17);
        //iy = (slope * ix) + bBE;
        cout << "iy2: " << iy;
    cout << "current: " << distanceCurrent << "\n";


    if( ix< 0) {
        ix = 0.000000000000;
        iy = (double)bBE;
    }

    if( iy< 0) {
        iy = 0.0000000000;
        ix = (iy + bBE )/ slope;
    }

    if( ix> 1) {
        ix = 1.000;
        iy = (double)(slope * ix) + (double)bBE;
    }

    if( iy> 1) {
        iy = 1.0000;
        ix = (iy + bBE) / slope;
    }

    Ecoords[0] = (int)(800*ix);
    Ecoords[1] = (int)(800*iy);
//
//    cout << "EXval: " << Ecoords[0];
//    cout << "EYval: " << Ecoords[1];



    double n = bx;
    double ny = (slope * n) + bBE;
  while( n< 1 &&  0 < n && ny< 1 && 0< ny)
  {
      n = n + 0.000001;
      ny = (slope * n) + bBE;
  }
    double zx = ix;
    double zy = (slope * zx) + bBE;
    while(zx< 1 &&  0 < zx && zy< 1 && 0< zy)
    {
        zx = zx - 0.0000001;
        zy = (slope * zx) + bBE;
    }
    cout << "iy1: " << iy;
    matrix[(int)(800*(iy))][(int)(800*ix)] = 1;
//    bresenham((int)(800*bx), (int)(800*by),(int)(800*ix) ,(int)(800*iy));
//    bresenham((int)(800*bx), (int)(800*by),(int)(800*n), (int)(800*ny));
    bresenham((int)(800*ix) ,(int)(800*iy),(int)(800*n), (int)(800*ny));

}

double getDistance(double x, double y, double a, double b) {

      return (double)sqrt((double)pow(x - a, 2) + (double)pow(y - b, 2));

}


double getSlope(double y1, double y2, double x1, double x2) {
    return (double)((double)(y2-y1)/(double)(x2-x1));
}

void bresenham(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1 ;
    int dy = y2 - y1 ;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
    if (dy<0){
        dy1 = -1 ;
    }
    else if (dy>0){
        dy1 = 1 ;
    }
    if (dx<0) {
        dx1 = -1;
    }
    else if (dx>0){
        dx1 = 1 ;}
    if (dy<0){
        dy2 = -1;
    }
    else if (dy>0){
        dy2 = 1 ;
    }
    int longest = abs(dy) ;
    int shortest = abs(dx) ;
    if (!(longest>shortest)) {
        longest = abs(dx) ;
        shortest = abs(dy) ;
        if (dx<0)
        {
            dx2 = -1 ;
        }

        else if (dx>0) {
            dx2 = 1;
        }
        dy2 = 0 ;
    }
    int numerator = longest >> 1 ;

    for (int i=0;i<=longest;i++) {
        matrix[y1][x1] = 1;
        numerator += shortest ;
        if (!(numerator<longest)) {
            numerator -= longest ;
            x1 += dx1 ;
            y1 += dy1 ;
        } else {
            x1 += dx2 ;
            y1 += dy2 ;
        }
    }

}




