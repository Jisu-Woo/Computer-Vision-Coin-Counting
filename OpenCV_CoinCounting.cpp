
#include <iostream>
#include <opencv2/core.hpp>   //이미지 관리
#include <opencv2/highgui.hpp>  //이미지 읽고 세이브, 화면에 보여주기
#include <opencv2/imgproc.hpp>  //이미지 프로세싱
#include <vector>

#ifdef _DEBUG 
#pragma comment (lib, "opencv_world480d.lib")    //debug용 라이브러리
#else
#pragma comment (lib, "opencv_world480.lib")
#endif

using namespace cv;
using pyramid = std::vector<Mat>;


int main()
{
    //Coin image reading
    Mat img = imread("C:/Users/gemge/OneDrive/바탕 화면/컴퓨터비젼/coins0.jpg");


    Mat smoothed;
    GaussianBlur(img, smoothed, Size(), 4);  //가우시안 필터링
    imshow("img", smoothed);
    waitKey();

    Mat grayimg;
    cvtColor(smoothed, grayimg, COLOR_BGR2GRAY);  //흑백 이미지로 변환
    imshow("img", grayimg);
    waitKey();

    Mat edge;
    Canny(smoothed, edge, 0, 70);  //Canny Edge detector
    imshow("img", edge);
    waitKey();


    std::vector<Vec3f> circles;

    HoughCircles(edge, circles, HOUGH_GRADIENT, 1.5, 80, 900, 65);   //Hough Circle Transform 


    int cnt = 0;   //detect한 원의 개수 카운팅 변수

    for (auto& c : circles) {
        circle(img, Point(c[0], c[1]), c[2], Scalar(255, 0, 255), 3, LINE_AA);
        cnt++;
    }
    imshow("circles", img);
    std::cout << cnt << std::endl;
    waitKey();
}