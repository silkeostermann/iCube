#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdio>

#include "BinaryMath.h"

using namespace std;


// BinaryMath structures
// ----------------------------------------------------------------------------

struct A_B_distance
{
	int A;
	int B;
	int dist;

	A_B_distance(int A, int B, int dist)
	{
		this->A = A;
		this->B = B;
		this->dist = dist;
	}
};

// BinaryMath functions
// ----------------------------------------------------------------------------

bool compare(const A_B_distance &x, const A_B_distance &y)
{
	return x.dist < y.dist;
}

string operation_addition(string* numbers,int count)
{
	if (count <= 1) return numbers[0];
	string result = numbers[0];
	for (int i=1; i < count; i++)
	{
		string next = numbers[i];
		int carry = 0;
		if (result.size() > next.size())
		{
			for (int j= (int)next.size(); j < (int)result.size(); j++)
				next = '0' + next;
		} else
		{
		    for (int j= (int)result.size(); j < (int)next.size(); j++)
				result = '0' + result;
		}
		next = '0' + next;
		result = '0' + result;
		cout << next.size() << ' ' << result.size() << endl;
		int k = result.size();
		while (k > 0)
		{
			int temp = carry + (((int)result[k]-48) + ((int)next[k]-48));
			switch (temp)
			{
			case 0: result[k] = '0'; carry = 0; break;
			case 1: result[k] = '1'; carry = 0; break;
			case 2: result[k] = '0'; carry = 1; break;
			case 3: result[k] = '1'; carry = 1; break;
			}
			k--;
		}
		result[0] = (char)(carry+48);
	}
	return result;
}

string operation_AND(string* numbers,int count)
{
	if (count <= 1) return numbers[0];
	string result = numbers[0];
	for (int i=1; i < count; i++)
	{
		string next = numbers[i];
		if (result.size() > next.size())
		{
			for (int j= (int)next.size(); j < (int)result.size(); j++)
				next = '0' + next;
		} else
		{
		    for (int j= (int)result.size(); j < (int)next.size(); j++)
				result = '0' + result;
		}
		cout << next.size() << ' ' << result.size() << endl;
		int k = result.size();
		while (k > 0)
		{
			int temp = ((int)result[k]-48) * ((int)next[k]-48);
			result[k] = (char)(temp+48);
			k--;
		}
	}
	return result;
}

string operation_OR(string* numbers,int count)
{
	if (count <= 1) return numbers[0];
	string result = numbers[0];
	for (int i=1; i < count; i++)
	{
		string next = numbers[i];
		if (result.size() > next.size())
		{
			for (int j= (int)next.size(); j < (int)result.size(); j++)
				next = '0' + next;
		} else
		{
		    for (int j= (int)result.size(); j < (int)next.size(); j++)
				result = '0' + result;
		}
		cout << next.size() << ' ' << result.size() << endl;
		int k = result.size();
		while (k > 0)
		{
			int temp = ((int)result[k]-48) + ((int)next[k]-48);
			if (temp == 0)
			{
				result[k] = '0';
			}
			else
				result[k] = '1';
			k--;
		}
	}
	return result;
}

string operation_XOR(string* numbers,int count)
{
	if (count <= 1) return numbers[0];
	string result = numbers[0];
	for (int i=1; i < count; i++)
	{
		string next = numbers[i];
		if (result.size() > next.size())
		{
			for (int j= (int)next.size(); j < (int)result.size(); j++)
				next = '0' + next;
		} else
		{
		    for (int j= (int)result.size(); j < (int)next.size(); j++)
				result = '0' + result;
		}
		cout << next.size() << ' ' << result.size() << endl;
		int k = result.size();
		while (k > 0)
		{
			int temp = ((int)result[k]-48) + ((int)next[k]-48);
			switch (temp)
			{
			case 0: result[k] = '1'; break;
			case 1: result[k] = '0'; break;
			case 2: result[k] = '1'; break;
			}
			k--;
		}
	}
	return result;
}

void operation_NOT(string* numbers, int count)
{
	for (int i=0; i< count; i++)
		for (int j=0; j< (int)numbers[i].size(); j++)
			if (numbers[i][j] == '0')
			{
				numbers[i][j] = '1';
			}
			else numbers[i][j] = '0';
}

int dist(Square square1, Square square2)
{
	CvPoint s1 = square1.GetCenterCoordinates();
	CvPoint s2 = square2.GetCenterCoordinates();
	int dx = s1.x - s2.x;
	int dy = s1.y - s2.y;
	//cout << dx << " " << dy << endl;
	return (dx*dx + dy*dy);
	//return (int)sqrt((double)((point1.x-point2.x)*(point1.x-point2.x)+(point1.y-point2.y)*(point1.y-point2.y)));
}

// BinaryMath class
// ----------------------------------------------------------------------------

BinaryMath::BinaryMath() {
	this->moduleConfig = new ModuleConfig("BinaryMath");
}


QString BinaryMath::moduleName() {
  return "Binary Math";
}

// Constructor
void BinaryMath::ProcessSquares(const Square* recognizedSquares, int size)
{
  // Put NumberSquares and OperatorSquares into 2 separate vectors
	//   vector <Square> testSquares;
	//   testSquares.push_back(Square(0,cvPoint(10,20),1,1)); // 0
	//   testSquares.push_back(Square(1,cvPoint(20,20),1,1)); // 1
	// testSquares.push_back(Square(1,cvPoint(30,20),1,1)); // 1
	//   testSquares.push_back(Square(2,cvPoint(40,20),1,1)); // Operator
	
	/*
	size = 3;
	Square recognizedSquares[3];
	recognizedSquares[0] = Square(0, cvPoint(10, 20), 1, 1);
	recognizedSquares[1] = Square(1, cvPoint(20, 20), 1, 1);
	recognizedSquares[2] = Square(2, cvPoint(30, 20), 1, 1);
	*/
  


	int NumberOfSquares = size; 
	int threshold = 6;
	
	vector <Square> OperatorSquares;
	vector <Square> NumberSquares;
	for (int i=0; i < NumberOfSquares;i++)
	{
		Square square = recognizedSquares[i];
		QString objectName = this->moduleConfig->objectForSquare(&square);
		printf("Square: %d (%s)\n", square.GetContoursCount(), qPrintable(objectName));
		if (this->isSquareNumber(&square))
			NumberSquares.push_back(square);
		else
			OperatorSquares.push_back(square);
	}

	// Create distance list
	
	vector <A_B_distance> DistanceList;

	if (NumberSquares.size() > 0) {
		for (int i = 0; i < NumberSquares.size()-1; i++) {
			for (int j=i+1; j < NumberSquares.size(); j++) {
				DistanceList.push_back(A_B_distance (i,j,dist(NumberSquares[i],NumberSquares[j])));
			}
		}
	}

	for (int i=0; i < (int)DistanceList.size(); i++)
		cout << DistanceList[i].A << ' ' <<DistanceList[i].B << ' ' << DistanceList[i].dist << endl;

	sort(DistanceList.begin(), DistanceList.end(), compare);

	cout << endl;

	for (int i=0;i < (int)DistanceList.size(); i++)
		cout << DistanceList[i].A << ' ' <<DistanceList[i].B << ' ' << DistanceList[i].dist << endl;

	//Create Clusterlist and SupportList
	vector <vector <int> > ClusterList;
	vector <int> SupportList;
	for (int i=0;i < (int)NumberSquares.size(); i++)
	{
		vector <int> Cluster;
		Cluster.push_back(i);
		ClusterList.push_back(Cluster);
		SupportList.push_back(i);
	}

	for (int i = 0; i < (int)DistanceList.size(); i++)
	{
		int Cl1 = SupportList[DistanceList[i].A];
		int Cl2 = SupportList[DistanceList[i].B];
		if (DistanceList[i].dist > threshold) break;
		if (Cl1 == Cl2) continue;
		vector <int> &Cluster1 = ClusterList[Cl1];
		vector <int> &Cluster2 = ClusterList[Cl2];
		for (int j = 0; j < (int)Cluster2.size(); j++)
		{
			Cluster1.push_back(Cluster2[j]);
			SupportList[Cluster2[j]] = Cl1;
		}
		Cluster2.clear();
	}
	//Remove empty clusters
	for(int i = 0; i < (int)ClusterList.size(); i++)
	{
		if (ClusterList[i].empty())
		{
			ClusterList.erase(ClusterList.begin() + i);
			i--;
		}
	}
	//Print Clusters
	for(int i = 0; i < (int)ClusterList.size(); i++)
	{
		cout << "Cluster" << i << ":\n";
		for(int j=0; j < (int)ClusterList[i].size(); j++)
		{
			cout << ClusterList[i][j] << endl;
		}
	}

	//Binary string generation
	cout << "Strings:" << endl;
	string* NumberBinStrings = new string [ClusterList.size()];
	for(int i = 0; i < (int)ClusterList.size(); i++)
	{
		//string str;
		for (int j = 0; j < (int)ClusterList[i].size(); j++)
		{
			Square *square = &(NumberSquares[ClusterList[i][j]]);
			NumberBinStrings[i] += this->binNumberCharForSquare(square);
		}
		cout << NumberBinStrings[i] << endl;
	}

	// Resolve operation
	char operation = this->resolveOperation(OperatorSquares);
	
  //Temporary config code for canvas size
  int width = 640;
  int height = 480;


	//Produce results
	string result = this->executeOperation(operation, NumberBinStrings, (int)ClusterList.size());
	cout << "The result is " << result << endl;

	if (operation == 'N')
		for(int i = 0; i < (int)ClusterList.size(); i++)
			cout << NumberBinStrings[i] << endl;
    
  // Drawing code
  QImage *qImage = new QImage(QSize(width, height), QImage::Format_RGB16);
  qImage->fill(QColor(255,255,255).rgb());
  QPainter *painter = new QPainter(qImage);
  painter->setPen(QColor(0,0,0));
  painter->setFont(QFont("Arial", 20));
  for(int i = 0; i < (int)ClusterList.size(); i++) {
		int x = NumberSquares[ClusterList[i][0]].GetCenterCoordinates().x;
		int y = 40;
    painter->drawText(x, y, NumberBinStrings[i].c_str());
  }

	if (operation) {
		char operationText[100];
		sprintf(operationText, "%c", operation);
		painter->drawText(20, 80, operationText);
	}

	painter->drawText(20, 120, result.c_str());

	unsigned int numberOfImages = 1;
  Image images[numberOfImages];
  images[0] = Image(*qImage, QPoint(22, 80));
  painter->end();

  SquaresProcessed(images, numberOfImages);
  
  delete [] NumberBinStrings;  
  delete qImage;
  delete painter;

}

string BinaryMath::executeOperation(char operation, string *numberStrings, int clusterSize) {
	if (clusterSize == 0) {
		return "NO INPUT";
	}

	switch (operation) {
		case '+':
			return operation_addition(numberStrings, clusterSize);
		case '&':
			return operation_AND(numberStrings, clusterSize);
		case '|':
			return operation_OR(numberStrings, clusterSize);
		case 'X':
			return operation_XOR(numberStrings, clusterSize);
		case 'N':
			operation_NOT(numberStrings, clusterSize);
			return "!";
		default:
			return "NO OP";
	}
}

char BinaryMath::resolveOperation(vector<Square> operatorSquares) {
	if (operatorSquares.size() == 0) {
		return 0;
	}

	Square *opSquare = &(operatorSquares[0]);
	QString objectName = this->moduleConfig->objectForSquare(opSquare);

	if (objectName == "plus") {
		return '+';
	} else if (objectName == "and") {
		return '&';
	}	else if (objectName == "or") {
		return '|';
	}	else if (objectName == "xor") {
		return 'X';
	} else if (objectName == "not") {
		return 'N';
	} else {
		return 0;
	}
}

bool BinaryMath::isSquareNumber(Square *square) {
	QString objectName = this->moduleConfig->objectForSquare(square);
	return (objectName == "0" || objectName == "1");
}

char BinaryMath::binNumberCharForSquare(Square *square) {
	QString objectName = this->moduleConfig->objectForSquare(square);

	if (objectName == "0") {
		return '0';
	} else if (objectName == "1") {
		return '1';
	} else {
		return '0'; // TODO: Default?
	}
}

//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

BinaryMath::~BinaryMath ()
{
	delete this->moduleConfig;
}
//NumberSquares
/*
QPainter painter;
painter.begin(&tmpImage);
painter.setPen(fontColor); // The font color comes from user select on a QColorDialog
painter.setFont(QFont("Chicago", fontSize)); // The font size comes from user input
painter.setCompositionMode(QPainter::CompositionMode_Source);
 
painter.drawText(penPos.x(), penPos.y(), QString::number(num));  // Draw a number on the image
*/
