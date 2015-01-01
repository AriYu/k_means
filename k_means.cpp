#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;

class Point
{
public:
  double x;
  double y;
};

class Cluster
{
public:
  Cluster(int cluster_num){
	centroids.resize(cluster_num);
	copy_centroids.resize(cluster_num);
	clusters.resize(cluster_num);
  }
public:
  vector<Point> centroids;
  vector<Point> copy_centroids;
  std::vector< std::vector<int> > clusters;
};

int ReadDataFromFile(string filename, vector<Point> &data, string splitchar=",")
{
  ifstream infile; 
  string tmpdata;
  Point point;
  vector<string> chardata;

  infile.open(filename.c_str());
  if (!infile)
	{
	  cout << "Unable to open input."<< endl;
	  return 1;
	}
  while(getline(infile, tmpdata)){
	boost::algorithm::split(chardata, tmpdata, boost::algorithm::is_any_of(splitchar.c_str()));
	point.x = stof(chardata[0]);
	point.y = stof(chardata[1]);
	data.push_back(point);
  }

  infile.close();
  return 0;
} 

double euclidean_distance(Point p1, Point p2)
{
  double distance = pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2);
  return sqrt(distance);
}

int main(void)
{
  string input  = "faithful.txt";
  string output = "clustered.txt";
 
  const int num_of_cluster = 2;
  Cluster cluster(num_of_cluster);
 
  ofstream outfile;
  outfile.open(output.c_str());

  vector<Point> points;
  if(ReadDataFromFile(input, points) == 1){
	return -1;
  }
  cout << "start clustering ..." << endl;

  srand(time(NULL));
  int index = 0;
  int points_num = (int)points.size();
  for(int i = 0; i < num_of_cluster; i++){
	index = rand() % points_num;
	cluster.centroids[i] = points[index];
  }

  vector<double> distance(num_of_cluster);

  int flag = true;
  int step = 0;
  while(flag)
  	{
	  step++;
	  for(int i = 0; i < num_of_cluster; i++){
		cluster.clusters[i].clear();
	  }

	  for(int i = 0; i < points_num; i++){
		for(int j = 0; j < num_of_cluster; j++){
		  distance[j] = euclidean_distance(points[i] , cluster.centroids[j]);
		}
		int id = 0;
		double min_distance = distance[0];
		for(int j = 0; j < num_of_cluster; j++){
		  if(distance[j] < min_distance){
			min_distance = distance[j];
			id = j;
		  }
		}
		cluster.clusters[id].push_back(i);
	  }
	  
	  cluster.copy_centroids = cluster.centroids;

	  // update centroid
	  Point centroid;
	  for(int i = 0; i < num_of_cluster; i++){
		centroid.x = 0;
		centroid.y = 0;
		cout << "cluster[" << i << "], size : " << cluster.clusters[i].size() << endl;
		for(int j = 0; j < (int)cluster.clusters[i].size(); j++){
		  centroid.x += points[cluster.clusters[i][j]].x;
		  centroid.y += points[cluster.clusters[i][j]].y;
		}
		centroid.x = centroid.x / (double)cluster.clusters[i].size();
		centroid.y = centroid.y / (double)cluster.clusters[i].size();
		cluster.centroids[i] = centroid;
	  }


	  double sum = 0;
	  for(int i = 0; i < num_of_cluster; i++){
		sum += euclidean_distance(cluster.copy_centroids[i], cluster.centroids[i]);
	  }

	  if( sum == 0.0){
	  	flag = false;
	  }else{
		cout << "sum : " << sum << endl;
	  }
	}

  for(int i = 0; i < num_of_cluster; i++){
	for(int j = 0; j < (int)cluster.clusters[i].size(); j++){
	  outfile << points[cluster.clusters[i][j]].x << " " << points[cluster.clusters[i][j]].y << endl;
	}
	outfile << endl; outfile << endl;
  }
 
  cout << "Finished" << endl;
  cout << "> Number of point:" << points_num << endl; 
  cout << "> Number of cluster:" << num_of_cluster << endl;
  cout << "> Number of iteration:" << step << endl;

  
  
  return 0;   
}
