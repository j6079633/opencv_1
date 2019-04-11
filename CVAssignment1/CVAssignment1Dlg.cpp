
// CVAssignment1Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "CVAssignment1.h"
#include "CVAssignment1Dlg.h"
#include "afxdialogex.h"

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "conio.h"
#include <algorithm>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\calib3d\calib3d.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\nonfree\features2d.hpp>
using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCVAssignment1Dlg 對話方塊



CCVAssignment1Dlg::CCVAssignment1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCVAssignment1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCVAssignment1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCVAssignment1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CCVAssignment1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CCVAssignment1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CCVAssignment1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCVAssignment1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCVAssignment1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCVAssignment1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCVAssignment1Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCVAssignment1Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCVAssignment1Dlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CCVAssignment1Dlg 訊息處理常式

BOOL CCVAssignment1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO:  在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CCVAssignment1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CCVAssignment1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CCVAssignment1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CCVAssignment1Dlg::OnBnClickedButton1()
{
	// 1.1 Find Corners
	// TODO: 在此加入控制項告知處理常式程式碼

	string imageName("..\\data\\1.bmp");
	Mat image;

	Size patSize(11, 8);
	vector<Point2f> centers;
	image = imread(imageName.c_str());
	if (image.empty()){
		//cout << "load failed\n";
	}
	bool found = findChessboardCorners(image, patSize, centers, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
		+ CALIB_CB_FAST_CHECK);
	if (!found) {
		cout << "found failed\n";
	}
	
	drawChessboardCorners(image, patSize, centers, found);
	imshow("1.1 Find Corners", image);
	waitKey(0);
	image.release();
}


void CCVAssignment1Dlg::OnBnClickedButton2()
{
	// 1.2 intrisic matrix
	// TODO: 在此加入控制項告知處理常式程式碼
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	string imageName;
	Mat image;
	Size patSize(11, 8);
	vector<Point2f> centers;
	vector<Point3f> objPoints;
	vector<vector<Point2f> > m_srcPoints;
	vector<vector<Point3f> > m_dstPoints;
	int i;
	for (i = 0; i < patSize.height; i++) {
		for (int j = 0; j < patSize.width; j++) {
			objPoints.push_back(Point3f(i, j, 0.0f));
		}
	}
	for (i = 1; i <= 21; i++) {

		imageName = "..\\data\\" + to_string(i);
		imageName = imageName + ".bmp";
		image = imread(imageName.c_str());
		if (image.empty()) {
			cout << "load failed\n";
		}

		bool found = findChessboardCorners(image, patSize, centers, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE);
		//TermCriteria param(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1);
		//cornerSubPix(image, centers, Size(5, 5), Size(-1, -1), param);
		if (centers.size() == patSize.area()){
			m_srcPoints.push_back(centers);
			m_dstPoints.push_back(objPoints);
		}
	}
	
	calibrateCamera(m_dstPoints, m_srcPoints, image.size(), cameraMatrix, distCoeffs, rvecs, tvecs);
	int j, k;


	for (j = 0; j < cameraMatrix.size().height; j++)
	{
		for (k = 0; k < cameraMatrix.size().width; k++)
		{
			cout << fixed << setprecision(6) << cameraMatrix.at<double>(j, k) << " ";
		}
		cout << endl;
	}
	waitKey(0);
	FreeConsole();
}


void CCVAssignment1Dlg::OnBnClickedButton3()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	int i, j;
	Mat rmat;
	Rodrigues(rvecs[0], rmat);
	for (i = 0; i<rmat.size().height; i++)
	{
		for (j = 0; j<rmat.size().width; j++)
		{
			cout << (rmat.at<double>(i, j)) << " ";			
		}
		cout << tvecs.at(0).at<double>(i);
		cout << endl;
	}
	waitKey(0);
	FreeConsole();
}


void CCVAssignment1Dlg::OnBnClickedButton4()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	int i, j;
	
	for (j = 0; j<distCoeffs.size().width; j++)
		{
			cout << (distCoeffs.at<double>(0, j)) << " ";
		}	
	waitKey(0);
	FreeConsole();
}


void CCVAssignment1Dlg::OnBnClickedButton5()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	vector<Point3f> objectPoint;
	vector<Point2f> imgPoint(5, {0.0f, 0.0f});
	String imgName;
	Mat showImage;
	namedWindow("2. AR", WINDOW_AUTOSIZE);
	objectPoint.push_back({0, 0, 2 });
	objectPoint.push_back({ 1, 1, 0});
	objectPoint.push_back({ 1, -1, 0});
	objectPoint.push_back({ -1, -1, 0});
	objectPoint.push_back({ -1, 1, 0 });
	
	for (int i = 1; i <= 5; i++){
		projectPoints(objectPoint, rvecs[i-1], tvecs[i-1], cameraMatrix, distCoeffs, imgPoint);
		imgName = "..\\data\\" + to_string(i);
		imgName = imgName + ".bmp";
		showImage = imread(imgName, IMREAD_COLOR);
		line(showImage, imgPoint[0], imgPoint[1], Scalar(0, 0, 255), 2, CV_AA);
		line(showImage, imgPoint[0], imgPoint[2], Scalar(0, 0, 255), 2, CV_AA);
		line(showImage, imgPoint[0], imgPoint[3], Scalar(0, 0, 255), 2, CV_AA);
		line(showImage, imgPoint[0], imgPoint[4], Scalar(0, 0, 255), 2, CV_AA);
		line(showImage, imgPoint[1], imgPoint[2], Scalar(0, 0, 255), 2, CV_AA);
		line(showImage, imgPoint[1], imgPoint[4], Scalar(0, 0, 255), 2, CV_AA);
		line(showImage, imgPoint[2], imgPoint[3], Scalar(0, 0, 255), 2, CV_AA);
		line(showImage, imgPoint[3], imgPoint[4], Scalar(0, 0, 255), 2, CV_AA);
		imshow("2. AR", showImage);
		waitKey(500);
	}
	
	waitKey(0);
}

vector<Point2d> mousePoint;
int pts_x[] = { 0, 0, 0, 0 };
int pts_y[] = { 0, 0, 0, 0 };
void onMouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN) {
		Point2d p;
		p.x = x;
		p.y = y;
		mousePoint.push_back(p);

		if (mousePoint.size() == 4) {
			cvDestroyAllWindows();
		}
	}
}
void CCVAssignment1Dlg::OnBnClickedButton6()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	Mat src, warp_dst;
	src = imread("..\\data\\QrCode.jpg", IMREAD_COLOR);
	namedWindow("source", WINDOW_AUTOSIZE);
	imshow("source", src);
	setMouseCallback("source", onMouse, NULL);
	waitKey(0);
	Point2f srcPoint[4];
	Point2f dstPoint[4];
	Mat warp_mat;
	srcPoint[0] = mousePoint[0];
	srcPoint[1] = mousePoint[1];
	srcPoint[2] = mousePoint[2];
	srcPoint[3] = mousePoint[3];
	dstPoint[0] = Point2f(20, 20);
	dstPoint[1] = Point2f(450, 20);
	dstPoint[2] = Point2f(450, 450);
	dstPoint[3] = Point2f(20, 450);
	warp_mat = getPerspectiveTransform(srcPoint, dstPoint);
	warpPerspective(src, warp_dst, warp_mat, Size(480, 480), INTER_LINEAR);

	imshow("3. Transformation", warp_dst);
	waitKey(0);
}

void CCVAssignment1Dlg::OnBnClickedButton7()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	Mat left = imread("..\\data\\SceneL_new.png", IMREAD_COLOR);	
	Mat right = imread("..\\data\\SceneR_new.png", IMREAD_COLOR);
	Mat g1, g2, disp, disp8;
	cvtColor(left, g1, CV_BGR2GRAY);
	cvtColor(right, g2, CV_BGR2GRAY);
	StereoBM sbm;
	
	sbm.state->SADWindowSize = 9;
	sbm.state->numberOfDisparities = 48;
	//sbm.state->minDisparity = 0;
	sbm.state->disp12MaxDiff = 1;
	sbm(g1, g2, disp);	
	normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
	imshow("4.1 Disparity", disp8);
	waitKey(0);
}


void CCVAssignment1Dlg::OnBnClickedButton8()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	Mat left = imread("..\\data\\SceneL_new.png", IMREAD_COLOR);
	Mat right = imread("..\\data\\SceneR_new.png", IMREAD_COLOR);
	Mat g1, g2, disp_check, disp, disp8, disp8_check;
	cvtColor(left, g1, CV_BGR2GRAY);
	cvtColor(right, g2, CV_BGR2GRAY);
	StereoBM sbm;

	sbm.state->SADWindowSize = 9;
	sbm.state->numberOfDisparities = 48;
	//sbm.state->minDisparity = 0;
	sbm.state->disp12MaxDiff = -1;

	sbm(g1, g2, disp);

	StereoBM sbm2;
	sbm2.state->SADWindowSize = 9;
	sbm2.state->numberOfDisparities = 48;
	//sbm2.state->minDisparity = 0;
	sbm2.state->disp12MaxDiff = 1;
	sbm2(g1, g2, disp_check);

	normalize(disp, disp8, 0, 255, CV_MINMAX, CV_8U);
	normalize(disp_check, disp8_check, 0, 255, CV_MINMAX, CV_8U);
	imshow("Disparity without check", disp8);
	imshow("Disparity with check", disp8_check);
	Mat diff, cmpResult;
	cvtColor(disp8, cmpResult, CV_GRAY2BGR);
	absdiff(disp8, disp8_check, diff);
	//imshow("diff", diff);
	
	Mat nonZeroCoordinates;
	findNonZero(diff, nonZeroCoordinates);
	for (int i = 0; i < nonZeroCoordinates.total(); i++) {
		
		cmpResult.at<Vec3b>(nonZeroCoordinates.at<Point>(i).y, nonZeroCoordinates.at<Point>(i).x) = Vec3b(0, 0, 255);
	}
	imshow("Difference", cmpResult);
	waitKey(0);
}


void CCVAssignment1Dlg::OnBnClickedButton9()
{
	// TODO:  在此加入控制項告知處理常式程式碼
	
	Mat queryImg = imread("..\\data\\plane1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat trainImg = imread("..\\data\\plane2.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	//resize(img1, queryImg, Size(img1.cols*0.4, img1.rows*0.4));
	//resize(img2, trainImg, Size(img2.cols*0.4, img2.rows*0.4));
	
	SiftFeatureDetector detector(400);
	vector<KeyPoint> queryKeypoints, trainKeypoints;
	detector.detect(queryImg, queryKeypoints);
	detector.detect(trainImg, trainKeypoints);

	drawKeypoints(queryImg, queryKeypoints, queryImg);
	drawKeypoints(trainImg, queryKeypoints, trainImg);
	imshow("query", queryImg);
	imshow("train", trainImg);
	SiftDescriptorExtractor extractor;
	Mat queryDescriptors, trainDescriptors;
	extractor.compute(queryImg, queryKeypoints, queryDescriptors);
	extractor.compute(trainImg, trainKeypoints, trainDescriptors);

	Size size = queryDescriptors.size();
	
	size = trainDescriptors.size();
	
	BFMatcher matcher(NORM_L2);
	vector<DMatch> matches;
	matcher.match(queryDescriptors, trainDescriptors, matches);
	double max_dist = 0;
	double min_dist = 10000;
	for (int i = 0; i < matches.size(); ++i) {
		if (matches[i].distance < min_dist)
			min_dist = matches[i].distance;
		if (matches[i].distance > max_dist)
			max_dist = matches[i].distance;
	}
	
	vector<DMatch> goodMatches;
	for (int j = 0; j < matches.size(); j++) {
		if (matches[j].distance < 6*min_dist)
			goodMatches.push_back(matches[j]);
	}
	
	
	Mat img_matches;
	drawMatches(queryImg, queryKeypoints, trainImg, trainKeypoints, goodMatches, img_matches);
	namedWindow("5. SIFT", WINDOW_NORMAL);
	imshow("5. SIFT", img_matches);
	waitKey(0);
	img_matches.release();
	destroyWindow("5. SIFT");

}
