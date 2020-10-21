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

void drawPerpSimple(double x, double y, double slopeofPerp, int i);

void drawSquare(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int i);

double getIntersectionX(double d, double d1, double d2, double d3, double d4, double d5, double d6, double d7);

double getIntersectionY(double d, double d1, double d2, double d3, double d4, double d5, double d6, double d7);

void drawPerpSimpleLine(double x2, double y2, double slope, int i);

using namespace std;
int matrix[800][800];
int Ecoords[2];
double Edouble[2];
double pointsToFind[16];
double pointsOfSquare1[9];
double pointsOfSquare2[9];
double pointsOfSquare3[9];
double pointsOfSquare4[9];
double pointsOfSquare5[9];
double pointsOfSquare6[9];
double AreaSmallest;


int SquareSmallest;

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

//    double x1 = 0.12596813455501951;
//    double y1 = 0.14643746621275203;
//
//    double x2 = 0.17449463772331114;
//    double y2 = 0.73137621569045641;
//
//    double x3 = 0.24005710950123943;
//    double y3 = 0.63983938733108314;
//
//    double x4 = 0.78058287351419353;
//    double y4 = 0.25635515305043904;

    double x1 = 0.18161564989165929;
    double y1 = 0.49650563066499831;

    double x2 = 0.20331431012909329;
    double y2 = 0.66115298928800315;

    double x3 = 0.45457319864497819;
    double y3 = 0.36802270577105012;

    double x4 = 0.86330759605700857;
    double y4 = 0.82033753471480453;

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
         x4 = ((double) rand() / (RAND_MAX));
         y4 = ((double) rand() / (RAND_MAX));

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
    points[0]= round(800*x1);

    string gety1 = str.substr(21,19);
    double y1 = stold(gety1);
    points[1]= round(800*y1);

    string getx2 = str.substr(45,19);
    double x2 = stold(getx2);
    points[2]= round(800*x2);

    string gety2 = str.substr(65,19);
    double y2 = stold(gety2);
    points[3]= round(800*y2);

    string getx3 = str.substr(89,19);
    double x3 = stold(getx3);
    points[4]= round(800*x3);

    string gety3 = str.substr(109,19);
    double y3 = stold(gety3);
    points[5]= round(800*y3);

    string getx4 = str.substr(133,19);
    double x4 = stold(getx4);
    points[6]= round(800*x4);

    string gety4 = str.substr(153,19);
    double y4 = stold(gety4);
    points[7]= round(800*y4);

    cout << points[0]<< "  " << points[1] <<"\n"; //A
    cout << points[2]<< "  "  << points[3] <<"\n"; //B
    cout << points[4]<< "  " << points[5]<<"\n"; //C
    cout << points[6]<< "  " << points[7] <<"\n"; //D
    file.close();

    matrix[points[1]][points[0]] = 1;
    matrix[points[3]][points[2]] = 1;
    matrix[points[5]][points[4]] = 1;
    matrix[points[7]][points[6]] = 1;
    //bresenham(points[0], points[1], points[4], points[5]);
    AreaSmallest = 1.0;


//      drawSquare(x1, y1, x2, y2, x3, y3, x4, y4, 1); //  good
//      drawSquare(x1, y1, x4, y4, x3, y3, x2, y2, 2); //good
//      drawSquare(x1, y1, x4, y4, x2, y2, x3, y3, 3); // good
//      drawSquare(x4, y4, x2, y2, x3, y3, x1, y1, 4); // good
//      drawSquare(x3, y3, x1, y1, x2, y2, x4, y4, 5); // good
//      drawSquare(x3, y3, x4, y4, x2, y2, x1, y1, 6);

    drawSquare(x1, y1, x2, y2, x3, y3, x4, y4, 1, -1); //  good
    drawSquare(x1, y1, x2, y2, x3, y3, x4, y4, 2, 1); //good
    drawSquare(x1, y1, x4, y4, x2, y2, x3, y3, 3, -1); // good
    drawSquare(x1, y1, x4, y4, x2, y2, x3, y3, 4, 1); // good
    drawSquare(x1, y1, x3, y3, x2, y2, x4, y4, 5, -1); // good
    drawSquare(x1, y1, x3, y3, x2, y2, x4, y4, 6, 1);


      cout << "Square Smallest: "<<SquareSmallest << "\n";
      if(SquareSmallest == 1)
      {
          drawSquare(x1, y1, x2, y2, x3, y3, x4, y4, 7);
      }

    if(SquareSmallest == 2)
    {
        drawSquare(x1, y1, x4, y4, x3, y3, x2, y2, 7);
    }

    if(SquareSmallest == 3)
    {
        drawSquare(x1, y1, x4, y4, x2, y2, x3, y3, 7);
    }

    if(SquareSmallest == 4)
    {
        drawSquare(x4, y4, x2, y2, x3, y3, x1, y1, 7);
    }

    if(SquareSmallest == 5)
    {
        drawSquare(x3, y3, x1, y1, x2, y2, x4, y4, 7);
    }

    if(SquareSmallest == 6)
    {
        drawSquare(x3, y3, x4, y4, x2, y2, x1, y1, 7);
    }


    // cout << x4 << setprecision(17);

    std::ofstream myfile;
    myfile.open ("points.txt");

    myfile << "(" <<std::setprecision(17)<< x1 << "," << y1 << ") , ";
    myfile << "(" <<std::setprecision(17)<< x2 << "," << y2 << ") , ";
    myfile << "(" <<std::setprecision(17)<< x3 << "," << y3 << ") , ";
    myfile << "(" <<std::setprecision(17)<< x4 << "," << y4 << ")";

    myfile << "(" <<std::setprecision(17)<< pointsOfSquare1[0] << "," << pointsOfSquare1[1] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare1[2] << "," << pointsOfSquare1[3] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare1[4] << "," << pointsOfSquare1[5] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare1[6] << "," << pointsOfSquare1[7] << ")" << " Area: " << pointsOfSquare1[8]<< "\n";

    myfile << "(" <<std::setprecision(17)<< pointsOfSquare2[0] << "," << pointsOfSquare2[1] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare2[2] << "," << pointsOfSquare2[3] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare2[4] << "," << pointsOfSquare2[5] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare2[6] << "," << pointsOfSquare2[7] << ")" << " Area: " << pointsOfSquare2[8] << "\n";

    myfile << "(" <<std::setprecision(17)<< pointsOfSquare3[0] << "," << pointsOfSquare3[1] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare3[2] << "," << pointsOfSquare3[3] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare3[4] << "," << pointsOfSquare3[5] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare3[6] << "," << pointsOfSquare3[7] << ")" << " Area: " << pointsOfSquare3[8]<< "\n";

    myfile << "(" <<std::setprecision(17)<< pointsOfSquare4[0] << "," << pointsOfSquare4[1] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare4[2] << "," << pointsOfSquare4[3] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare4[4] << "," << pointsOfSquare4[5] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare4[6] << "," << pointsOfSquare4[7] << ")" << " Area: " << pointsOfSquare4[8]<< "\n";

    myfile << "(" <<std::setprecision(17)<< pointsOfSquare5[0] << "," << pointsOfSquare5[1] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare5[2] << "," << pointsOfSquare5[3] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare5[4] << "," << pointsOfSquare5[5] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare5[6] << "," << pointsOfSquare5[7] << ")" << " Area: " << pointsOfSquare5[8]<< "\n";

    myfile << "(" <<std::setprecision(17)<< pointsOfSquare6[0] << "," << pointsOfSquare6[1] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare6[2] << "," << pointsOfSquare6[3] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare6[4] << "," << pointsOfSquare6[5] << ") , ";
    myfile << "(" <<std::setprecision(17)<< pointsOfSquare6[6] << "," << pointsOfSquare6[7] << ")" << " Area: " << pointsOfSquare6[8]<< "\n";
    myfile.close();

}

void drawSquare(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int squareNum) {
    double perpSlope = (double)-1 / (double)getSlope(y3,y1,x3, x1);
    double ac = getDistance(x1, y1, x3, y3);
   // bresenham(round(x1*800), round(y1*800), round(x3*800), round(y3*800));
    drawPerpendicularLine(x4, y4,  perpSlope, ac); // DE
    cout <<  Edouble[1] << setprecision(17) << "\n";
    cout <<  Edouble[1] << setprecision(17) << "\n";
    cout << Edouble[0] << setprecision(17) << "\n";
   // bresenham(Ecoords[0], Ecoords[1], round(x2*800), round(y2*800)); // BE
    double initSlope = (double)getSlope(y2, Edouble[1],x2, Edouble[0]);
    double slopeperpc = (double)-1 / (double)initSlope;
    //matrix[Ecoords[1]][Ecoords[0]] = 1;
  //  cout << "X4: " << x4 << setprecision(17) << "\n";
    drawPerpSimple(x2, y2, initSlope, 1);
    drawPerpSimple(x3, y3, slopeperpc, 2);
    drawPerpSimple(x4, y4, initSlope, 3);
    drawPerpSimple(x1, y1, slopeperpc, 4);

    if(squareNum == 7)
    {
        drawPerpSimpleLine(x2, y2, initSlope, 1);
        drawPerpSimpleLine(x3, y3, slopeperpc, 2);
        drawPerpSimpleLine(x4, y4, initSlope, 3);
        drawPerpSimpleLine(x1, y1, slopeperpc, 4);
    }



    // drawPerpendicularLine(x2, y2, (double)getSlope(y2, Edouble[1],x2, Edouble[0]), 0.50);
if(squareNum == 1) {
    // Intersection of  line 2 and line 3
    pointsOfSquare1[0] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                          pointsToFind[2], pointsToFind[3],
                                          pointsToFind[4], pointsToFind[5],
                                          pointsToFind[6], pointsToFind[7]);
    pointsOfSquare1[1] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                          pointsToFind[2], pointsToFind[3],
                                          pointsToFind[4], pointsToFind[5],
                                          pointsToFind[6], pointsToFind[7]);


    //Intersection of  line 4 and line 3
    pointsOfSquare1[2] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                          pointsToFind[10], pointsToFind[11],
                                          pointsToFind[4], pointsToFind[5],
                                          pointsToFind[6], pointsToFind[7]);
    pointsOfSquare1[3] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                          pointsToFind[10], pointsToFind[11],
                                          pointsToFind[4], pointsToFind[5],
                                          pointsToFind[6], pointsToFind[7]);

    //Intersection of  line 4 and line 1
    pointsOfSquare1[4] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                          pointsToFind[10], pointsToFind[11],
                                          pointsToFind[12], pointsToFind[13],
                                          pointsToFind[14], pointsToFind[15]);
    pointsOfSquare1[5] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                          pointsToFind[10], pointsToFind[11],
                                          pointsToFind[12], pointsToFind[13],
                                          pointsToFind[14], pointsToFind[15]);
    //Intersection of  line 2 and line 1
    pointsOfSquare1[6] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                          pointsToFind[2], pointsToFind[3],
                                          pointsToFind[12], pointsToFind[13],
                                          pointsToFind[14], pointsToFind[15]);
    pointsOfSquare1[7] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                          pointsToFind[2], pointsToFind[3],
                                          pointsToFind[12], pointsToFind[13],
                                          pointsToFind[14], pointsToFind[15]);

//    cout <<"Distance2: " <<getDistance(pointsOfSquare1[4], pointsOfSquare1[5],
//                        pointsOfSquare1[6], pointsOfSquare1[7])<< setprecision(17) << "\n";

    double side = getDistance(pointsOfSquare1[4], pointsOfSquare1[5],
                              pointsOfSquare1[6], pointsOfSquare1[7]);
    double Area = pow(side, 2);

    pointsOfSquare1[8] = Area;

    if(AreaSmallest > Area)
    {
        AreaSmallest = Area;
        SquareSmallest = 1;
    }

    cout << "Area1: " << Area << "\n";

}
    if(squareNum == 2) {
        // Intersection of  line 2 and line 3
        pointsOfSquare2[0] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare2[1] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);


        //Intersection of  line 4 and line 3
        pointsOfSquare2[2] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare2[3] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);

        //Intersection of  line 4 and line 1
        pointsOfSquare2[4] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare2[5] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        //Intersection of  line 2 and line 1
        pointsOfSquare2[6] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare2[7] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);

//    cout <<"Distance2: " <<getDistance(pointsOfSquare1[4], pointsOfSquare1[5],
//                        pointsOfSquare1[6], pointsOfSquare1[7])<< setprecision(17) << "\n";

        double side = getDistance(pointsOfSquare2[4], pointsOfSquare2[5],
                                  pointsOfSquare2[6], pointsOfSquare2[7]);
        double Area = pow(side, 2);

        pointsOfSquare2[8] = Area;
        if(AreaSmallest > Area)
        {
            AreaSmallest = Area;
            SquareSmallest = 2;
        }

        cout << "Area2: " << Area << "\n";

    }
    if(squareNum == 3) {
        // Intersection of  line 2 and line 3
        pointsOfSquare3[0] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare3[1] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);


        //Intersection of  line 4 and line 3
        pointsOfSquare3[2] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare3[3] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);

        //Intersection of  line 4 and line 1
        pointsOfSquare3[4] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare3[5] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        //Intersection of  line 2 and line 1
        pointsOfSquare3[6] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare3[7] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);

//    cout <<"Distance2: " <<getDistance(pointsOfSquare1[4], pointsOfSquare1[5],
//                        pointsOfSquare1[6], pointsOfSquare1[7])<< setprecision(17) << "\n";



        double side = getDistance(pointsOfSquare3[4], pointsOfSquare3[5],
                                  pointsOfSquare3[6], pointsOfSquare3[7]);
        double Area = pow(side, 2);

        pointsOfSquare3[8] = Area;

        if(AreaSmallest > Area)
        {
            AreaSmallest = Area;
            SquareSmallest = 3;
        }

        cout << "Area3: " << Area << "\n";


    }
    if(squareNum == 4) {
        // Intersection of  line 2 and line 3
        pointsOfSquare4[0] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare4[1] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);


        //Intersection of  line 4 and line 3
        pointsOfSquare4[2] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare4[3] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);

        //Intersection of  line 4 and line 1
        pointsOfSquare4[4] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare4[5] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        //Intersection of  line 2 and line 1
        pointsOfSquare4[6] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare4[7] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);

//    cout <<"Distance2: " <<getDistance(pointsOfSquare1[4], pointsOfSquare1[5],
//                        pointsOfSquare1[6], pointsOfSquare1[7])<< setprecision(17) << "\n";

        double side = getDistance(pointsOfSquare4[4], pointsOfSquare4[5],
                                  pointsOfSquare4[6], pointsOfSquare4[7]);
        double Area = pow(side, 2);

        pointsOfSquare4[8] = Area;
        if(AreaSmallest > Area)
        {
            AreaSmallest = Area;
            SquareSmallest = 4;
        }

        cout << "Area4: " << Area << "\n";


    }
    if(squareNum == 5) {
        // Intersection of  line 2 and line 3
        pointsOfSquare5[0] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare5[1] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);


        //Intersection of  line 4 and line 3
        pointsOfSquare5[2] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare5[3] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);

        //Intersection of  line 4 and line 1
        pointsOfSquare5[4] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare5[5] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        //Intersection of  line 2 and line 1
        pointsOfSquare5[6] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare5[7] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);

//    cout <<"Distance2: " <<getDistance(pointsOfSquare1[4], pointsOfSquare1[5],
//                        pointsOfSquare1[6], pointsOfSquare1[7])<< setprecision(17) << "\n";

        double side = getDistance(pointsOfSquare5[4], pointsOfSquare5[5],
                                  pointsOfSquare5[6], pointsOfSquare5[7]);
        double Area = pow(side, 2);
        if(AreaSmallest > Area)
        {
            AreaSmallest = Area;
            SquareSmallest = 5;
        }
        pointsOfSquare5[8] = Area;
        cout <<  setprecision(17) << "\n";
        cout << "Area5: " << Area <<  setprecision(17) << "\n";
//        cout << "X1: " << pointsOfSquare5[0] << setprecision(17) << "\n";
//        cout << "Y1: " << pointsOfSquare5[1] << setprecision(17) << "\n";
//        cout << "X2: " << pointsOfSquare5[2] << setprecision(17) << "\n";
//        cout << "Y2: " << pointsOfSquare5[3] << setprecision(17) << "\n";
//        cout << "X3: " << pointsOfSquare5[4] << setprecision(17) << "\n";
//        cout << "Y3: " << pointsOfSquare5[5] << setprecision(17) << "\n";
//        cout << "X4: " << pointsOfSquare5[6] << setprecision(17) << "\n";
//        cout << "Y4: " << pointsOfSquare5[7] << setprecision(17) << "\n";

    }
    if(squareNum == 6) {
        // Intersection of  line 2 and line 3
        pointsOfSquare6[0] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare6[1] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);


        //Intersection of  line 4 and line 3
        pointsOfSquare6[2] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);
        pointsOfSquare6[3] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[4], pointsToFind[5],
                                              pointsToFind[6], pointsToFind[7]);

        //Intersection of  line 4 and line 1
        pointsOfSquare6[4] = getIntersectionX(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare6[5] = getIntersectionY(pointsToFind[8], pointsToFind[9],
                                              pointsToFind[10], pointsToFind[11],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        //Intersection of  line 2 and line 1
        pointsOfSquare6[6] = getIntersectionX(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);
        pointsOfSquare6[7] = getIntersectionY(pointsToFind[0], pointsToFind[1],
                                              pointsToFind[2], pointsToFind[3],
                                              pointsToFind[12], pointsToFind[13],
                                              pointsToFind[14], pointsToFind[15]);

//    cout <<"Distance2: " <<getDistance(pointsOfSquare1[4], pointsOfSquare1[5],
//                        pointsOfSquare1[6], pointsOfSquare1[7])<< setprecision(17) << "\n";

        double side = getDistance(pointsOfSquare6[4], pointsOfSquare6[5],
                                  pointsOfSquare6[6], pointsOfSquare6[7]);
        double Area = pow(side, 2);
        if(AreaSmallest > Area)
        {
            AreaSmallest = Area;
            SquareSmallest = 6;
        }
        pointsOfSquare6[8] = Area;

        cout << setprecision(17) << "\n";
        cout << "Area6: " << Area <<  "\n";

//        cout << "X1: " << pointsOfSquare6[0] << setprecision(17) << "\n";
//        cout << "Y1: " << pointsOfSquare6[1] << setprecision(17) << "\n";
//        cout << "X2: " << pointsOfSquare6[2] << setprecision(17) << "\n";
//        cout << "Y2: " << pointsOfSquare6[3] << setprecision(17) << "\n";
//        cout << "X3: " << pointsOfSquare6[4] << setprecision(17) << "\n";
//        cout << "Y3: " << pointsOfSquare6[5] << setprecision(17) << "\n";
//        cout << "X4: " << pointsOfSquare6[6] << setprecision(17) << "\n";
//        cout << "Y4: " << pointsOfSquare6[7] << setprecision(17) << "\n";




    }


}

void drawPerpSimpleLine(double x, double y, double slopeofPerp, int sideNum) {
    double BsideC = (double)(slopeofPerp * (double)-1 * (double)x) - (double)((double)-1 * ((double)y));

    double cc = x;
    double ccy = slopeofPerp* cc + BsideC ;

    while(cc <= 1 && cc >= 0 && ccy <= 1 && ccy>= 0)
    {
        if(slopeofPerp >= 0)
            cc = cc - 0.000001;

        if(slopeofPerp < 0)
            cc= cc + 0.000001;

        ccy = slopeofPerp* cc + BsideC;
    }
    if(cc < 0) {
        cc = 0.000;
        ccy =  BsideC;
    }

    if(ccy < 0) {
        ccy = 0.000;
        cc = ( ccy-BsideC)/slopeofPerp;
    }

    if(cc > 1) {
        cc = 1.000;
        ccy = slopeofPerp* cc + BsideC;
    }
    if(ccy > 1) {
        ccy = 1.000;
        cc = ( ccy-BsideC)/slopeofPerp;
    }
    double ccm = x;
    double ccym = slopeofPerp* ccm + BsideC;

    while(ccm < 1 && ccm > 0 && ccym < 1 && ccym> 0)
    {
        if(slopeofPerp >= 0)
            ccm = ccm + 0.000001;

        if(slopeofPerp < 0)
            ccm= ccm - 0.000001;

        ccym = slopeofPerp* ccm + BsideC;
    }
    if(ccm < 0) {
        ccm = 0.000;
        ccym =  BsideC;
    }

    if(ccym < 0) {
        ccym = 0.000;
        ccm = ( ccym-BsideC)/slopeofPerp;
    }

    if(ccm > 1) {
        ccm = 1.000;
        ccym = slopeofPerp* ccm + BsideC;
    }
    if(ccym > 1) {
        ccym = 1.000;
        ccm = ( ccym-BsideC)/slopeofPerp;
    }


    if(sideNum == 1)
    {
        pointsToFind[0] = cc;
        pointsToFind[1] = ccy;
        pointsToFind[2] = ccm;
        pointsToFind[3] = ccym;
    }
    if(sideNum == 2)
    {
        pointsToFind[4] = cc;
        pointsToFind[5] = ccy;
        pointsToFind[6] = ccm;
        pointsToFind[7] = ccym;
    }
    if(sideNum == 3)
    {
        pointsToFind[8] = cc;
        pointsToFind[9] = ccy;
        pointsToFind[10] = ccm;
        pointsToFind[11] = ccym;
    }
    if(sideNum == 4)
    {
        pointsToFind[12] = cc;
        pointsToFind[13] = ccy;
        pointsToFind[14] = ccm;
        pointsToFind[15] = ccym;
    }
    bresenham(round(800*cc), round(800*ccy), round(800*ccm), round(800*ccym));

}

double getIntersectionY(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double m1 = dy / dx;
    double c1 = y1 - m1 * x1;

    double dx2 = x4 - x3;
    double dy2 = y4 - y3;
    double m2 = dy2 / dx2;
    double c2 = y4 - m2 * x4;

    double interX = (c2 - c1) / (m1 - m2);

    return m1 * interX + c1;

}

double getIntersectionX(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
   double dx = x2 - x1;
   double dy = y2 - y1;
   double m1 = dy / dx;
   double c1 = y1 - m1 * x1;

   double dx2 = x4 - x3;
   double dy2 = y4 - y3;
   double m2 = dy2 / dx2;
   double c2 = y4 - m2 * x4;

   return (c2 - c1) / (m1 - m2);
}

void drawPerpSimple(double x, double y, double slopeofPerp, int sideNum) {

    double BsideC = (double)(slopeofPerp * (double)-1 * (double)x) - (double)((double)-1 * ((double)y));

    double cc = x;
    double ccy = slopeofPerp* cc + BsideC;

    while(cc <= 1 && cc >= 0 && ccy <= 1 && ccy>= 0)
    {
        if(slopeofPerp >= 0)
            cc = cc - 0.000001;

        if(slopeofPerp < 0)
            cc= cc + 0.000001;

        ccy = slopeofPerp* cc + BsideC;
    }
    if(cc < 0) {
        cc = 0.000;
        ccy =  BsideC;
    }

    if(ccy < 0) {
        ccy = 0.000;
        cc = ( ccy-BsideC)/slopeofPerp;
    }

    if(cc > 1) {
        cc = 1.000;
        ccy = slopeofPerp* cc + BsideC;
    }
    if(ccy > 1) {
        ccy = 1.000;
        cc = ( ccy-BsideC)/slopeofPerp;
    }
    double ccm = x;
    double ccym = slopeofPerp* ccm + BsideC;

    while(ccm < 1 && ccm > 0 && ccym < 1 && ccym> 0)
    {
        if(slopeofPerp >= 0)
            ccm = ccm + 0.000001;

        if(slopeofPerp < 0)
            ccm= ccm - 0.000001;

        ccym = slopeofPerp* ccm + BsideC;
    }
    if(ccm < 0) {
        ccm = 0.000;
        ccym =  BsideC;
    }

    if(ccym < 0) {
        ccym = 0.000;
        ccm = ( ccym-BsideC)/slopeofPerp;
    }

    if(ccm > 1) {
        ccm = 1.000;
        ccym = slopeofPerp* ccm + BsideC;
    }
    if(ccym > 1) {
        ccym = 1.000;
        ccm = ( ccym-BsideC)/slopeofPerp;
    }


    if(sideNum == 1)
    {
        pointsToFind[0] = cc;
        pointsToFind[1] = ccy;
        pointsToFind[2] = ccm;
        pointsToFind[3] = ccym;
    }
    if(sideNum == 2)
    {
        pointsToFind[4] = cc;
        pointsToFind[5] = ccy;
        pointsToFind[6] = ccm;
        pointsToFind[7] = ccym;
    }
    if(sideNum == 3)
    {
        pointsToFind[8] = cc;
        pointsToFind[9] = ccy;
        pointsToFind[10] = ccm;
        pointsToFind[11] = ccym;
    }
    if(sideNum == 4)
    {
        pointsToFind[12] = cc;
        pointsToFind[13] = ccy;
        pointsToFind[14] = ccm;
        pointsToFind[15] = ccym;
    }
  //  bresenham(round(800*cc), round(800*ccy), round(800*ccm), round(800*ccym));

}

void drawPerpendicularLine(double bx, double by, double slope, double distance) {
    double bBE = (slope * -1 * bx) - (-1 * by); // y = slope * x + bBE
    double distanceCurrent;
//        cout << "x4: " << bx << setprecision(17) << "\n";
//        cout << "y4: " << by << setprecision(17) << "\n";
//        cout << "slope: " << slope << setprecision(17) << "\n";
//        cout << "b: " << bBE << setprecision(17) << "\n";
        double ix = bx;
        double iy = (slope * ix) - bBE;
       // cout << "distance: " << distance << setprecision(17) << "\n";
        while(distanceCurrent <= distance )
        {
            if(slope >= 0)
                ix = ix - 0.00001;

            if(slope < 0)
                ix= ix + 0.000001;

            iy = (double)(slope * ix) + (double)bBE;

            distanceCurrent = (double)getDistance(bx, by, ix, iy);
            //cout << "current: " << distanceCurrent << "\n";
        }
//        cout << "iy1: " << iy << setprecision(17);
//        //iy = (slope * ix) + bBE;
//        cout << "iy2: " << iy;
//    cout << "current: " << distanceCurrent << "\n";


    if( ix< 0) {
        ix = 0.000000000000;
        iy = (double)bBE;
    }

    if( iy< 0) {
        iy = 0.0000000000;
        ix = (iy + bBE )/ slope;

        if( ix< 0) {
            ix = 0.000000000000;
            iy = (double)bBE;
        }

    }


    if( ix> 1) {
        ix = 1.000;
        iy = (double)(slope * ix) + (double)bBE;
    }

    if( iy> 1) {
        iy = 1.0000;
        ix = (iy + bBE) / slope;
        if( ix> 1) {
            ix = 1.000;
            iy = (double)(slope * ix) + (double)bBE;
        }
    }

    Edouble[0] = ix;
    Edouble[1] = iy;
    Ecoords[0] = round(800*ix);
    Ecoords[1] = round(800*iy);
//
//    cout << "EXval: " << Ecoords[0];
//    cout << "EYval: " << Ecoords[1];



//    double n = bx;
//    double ny = (slope * n) + bBE;
//  while( n< 1 &&  0 < n && ny< 1 && 0< ny)
//  {
//      n = n + 0.0000001;
//      ny = (slope * n) + bBE;
//  }
//    double zx = ix;
//    double zy = (slope * zx) + bBE;
//    while(zx< 1 &&  0 < zx && zy< 1 && 0< zy)
//    {
//        zx = zx - 0.0000001;
//        zy = (slope * zx) + bBE;
//    }
//   // cout << "iy1: " << iy;
//    //matrix[(int)(800*(iy))][(int)(800*ix)] = 1;
//
//    bresenham(round(800*ix) ,round(800*iy),round(800*n), round(800*ny));

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




