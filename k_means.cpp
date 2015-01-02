#include "k_means.h"

using namespace std;

Kmeans::Kmeans(std::vector< std::vector<double> > &points,
			   int cluster_num,
			   int dim)
  : cluster_(cluster_num, dim), distance(cluster_num)
{
  points_ = points;
  dim_ = dim;
  cluster_num_ = cluster_num;
  points_num_ = points.size();
  srand(time(NULL));
  int index = 0;
  
  // 乱数でサンプルの中から最初の重心を選択する
  for(int i = 0; i < cluster_num_; i++){
	index = rand() % points_num_;
	cluster_.centroids[i] = points[index];
  }
}

Kmeans::~Kmeans()
{
}
double Kmeans::EuclideanDistance(std::vector<double> p1,
						 std::vector<double> p2)
{
  double distance = 0;
  for(int i = 0; i < dim_; i++){
	distance += pow(p1[i] - p2[i],2);
  }
  return sqrt(distance);
}
void Kmeans::UpdateCentroid()
{
  // update centroid
  vector<double> centroid(dim_);
  for(int i = 0; i < cluster_num_; i++){
	for(int j = 0; j < dim_; j++){
	  centroid[j] = 0;
	}
	cout << "cluster[" << i << "], size : " << cluster_.clusters[i].size() << endl;
	for(int j = 0; j < (int)cluster_.clusters[i].size(); j++){
	  for(int k = 0; k < dim_; k++){
		centroid[k] += points_[cluster_.clusters[i][j]][k];
	  }
	}
	for(int j = 0; j < dim_; j++){
	  centroid[j] = centroid[j] / (double)cluster_.clusters[i].size();
	}
	cluster_.centroids[i] = centroid;
  }
}

void Kmeans::Clustering(Cluster &result_clusters)
{

  int flag = true;
  int step = 0;
  while(flag)
  	{
	  step++;
	  for(int i = 0; i < cluster_num_; i++){
		cluster_.clusters[i].clear();
	  }

	  for(int i = 0; i < points_num_; i++){
		for(int j = 0; j < cluster_num_; j++){
		  distance[j] = EuclideanDistance(points_[i] , cluster_.centroids[j]);
		}
		int id = 0;
		double min_distance = distance[0];
		for(int j = 0; j < cluster_num_; j++){
		  if(distance[j] < min_distance){
			min_distance = distance[j];
			id = j;
		  }
		}
		cluster_.clusters[id].push_back(i);
	  }
	  
	  cluster_.copy_centroids = cluster_.centroids;

	  UpdateCentroid();

	  double sum = 0;
	  for(int i = 0; i < cluster_num_; i++){
		sum += EuclideanDistance(cluster_.copy_centroids[i], cluster_.centroids[i]);
	  }

	  if( sum == 0.0){
	  	flag = false;
	  }else{
		cout << "sum : " << sum << endl;
	  }
	}
  result_clusters = cluster_;
}


int ReadDataFromFile(string filename, 
					 vector< vector<double> > &data, 
					 string splitchar)
{
  ifstream infile; 
  string tmpdata;
  vector<double> point;
  vector<string> chardata;

  infile.open(filename.c_str());
  if (!infile)
	{
	  cout << "Unable to open input."<< endl;
	  return 1;
	}
  while(getline(infile, tmpdata)){
	boost::algorithm::split(chardata, tmpdata, boost::algorithm::is_any_of(splitchar.c_str()));
	if(point.size() != chardata.size()){
	  point.resize(chardata.size());
	}
	for(int i = 0; i < (int)chardata.size(); i++){
	  point[i] = stof(chardata[i]);
	}
	data.push_back(point);
  }

  infile.close();
  return 0;
} 
