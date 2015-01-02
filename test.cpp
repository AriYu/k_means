#include "k_means.h"

using namespace std;



int main(void)
{
  string input  = "faithful.txt";
  string output = "clustered.txt";
 
  const int num_of_cluster = 2;
  const int num_of_dimension = 2;

  ofstream outfile;
  outfile.open(output.c_str());

  vector< vector<double> > points;
  if(ReadDataFromFile(input, points) == 1){
	return -1;
  }

  Kmeans kmeans(points, num_of_cluster, num_of_dimension);
  Cluster result_cluster;
  
  cout << "start clustering ..." << endl;
  kmeans.Clustering(result_cluster);
  

  for(int i = 0; i < num_of_cluster; i++){
	for(int j = 0; j < (int)result_cluster.clusters[i].size(); j++){
	  for(int k = 0; k < num_of_dimension; k++){
		outfile << points[result_cluster.clusters[i][j]][k] << " " << flush;
	  }
	  outfile << endl;
	}
	outfile << endl; outfile << endl;
  }
 
  // cout << "Finished" << endl;
  // cout << "> Number of point:" << points_num << endl; 
  // cout << "> Number of cluster:" << num_of_cluster << endl;
  // cout << "> Number of iteration:" << step << endl;

  
  
  return 0;   
}
