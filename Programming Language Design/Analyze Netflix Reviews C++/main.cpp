//
//  C++ program to analyze Netflix reviews
//
//	Filip Radzikowski
//	U. of Illinois, Chicago
//	CS341, Spring 2015
//	Homework 3
//
//	C++ program that take two files: a movie list and a list of all reviews.
//	The program parses each line and distributes the data accordingly between
//	two classes (movie and review).
//

// Preprocessor commands
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Review class used for parsing and initializing review file data elements.
class review{
public:
	int movieID;
	int reviewerID;
	int rating;

	// Constructor recieves string line of review data 
	// which it parses and decleres movieID, reviewerID, and rating
	review(string currReview){
		// Transfor string into stream
		istringstream currentStream(currReview);
		string helpMovie, helpReviewer, helpRating;

		// Using getline() to parse each data element with ',' parser
		getline(currentStream, helpMovie, ',');
		getline(currentStream, helpReviewer, ',');
		getline(currentStream, helpRating, ',');

		// convert from string to integer and declare variables
		movieID = atoi(helpMovie.c_str() );
		reviewerID = atoi(helpReviewer.c_str() );
		rating = atoi(helpRating.c_str() );	
	}
}; // end review class

// Movie class used for parsing and initializing movie file data elements.
// Beyond the data file elements movieID and movieName three additional
// variables are declared to store total number of review (totalReviews)
// the calculated avarage of all review scores, and an array that stores
// the count of each individual score represented by the index number 
// of the array (scoringRage[])
class movie {
public:
	int movieID;			// numerical movie ID
	string movieName;
	int totalReviews;
	double avgReviewScore;	// average rating of movie
	int scoringRange[5];	// counter for possible movie scores
	
	// Constructor initialized totalReviews, avgReviewScore and the 
	// scoringRange[] elements to zero.
	movie(string currMovie){
		totalReviews = 0;
		avgReviewScore = 0.0;
		
		// Initialize all scores to 0 count
		for(int i = 0; i < 5; i++)
			scoringRange[i] = 0;
		
		// Parse data and initialize movieName and movieID
		istringstream currentStream(currMovie);
		string helperID;
		getline(currentStream, helperID, ',');
		getline(currentStream, movieName, ',');

		movieID = atoi(helperID.c_str());
	}
}; // end movie class 


// Passing movie vector and review vector from main by reference. Initializes
// average review score, total reviews and individual review scores for each 
// movie. This data is stored in a vector of movie classes by movie instance. 
// The movie vector is then sorted by decending average review scores and in the 
// instance that those are the same they are sorted in assending movie name 
// order.  
void getTop10Movies ( vector<movie> &movieVec, const vector<review> &reviewVec){
	
	int i;	// used for movieID index
	// Accumulate all the raw review scores for each movie and increment
	// the total number of reviews. Initialize these values in movie vector.
	for(auto x : reviewVec){
		i = x.movieID - 1; // adjust index to match movieID
		// accumulating raw scores and storing temporarily in avgRevewScore
		movieVec[i].avgReviewScore += x.rating;
		// incrementing total review per movie
		movieVec[i].totalReviews++;
		// increment each individual score per movie
		movieVec[i].scoringRange[x.rating - 1]++;
	}	

	// initialize average review score for each movie
	for(auto& x : movieVec){ x.avgReviewScore/=x.totalReviews;}

	// sorting averages in decending order and in the case they are the same
	// then sorted in assending movie name order. 
	sort(movieVec.begin(), movieVec.end(), [](movie& m1, movie& m2){
		// using turnary operator to eliminate if()else() statements
		return (m1.avgReviewScore == m2.avgReviewScore) 
				? (m1.movieName < m2.movieName) 
				: m1.avgReviewScore > m2.avgReviewScore;
	});

	// print out result for top 10 movies
	cout << "\n>> Top 10 Movies <<\n" << endl;
	cout << "Rank\tID\tReviews\tAvg\tName" << endl;
	for (int i = 0; i < 10; i++){
		cout << i + 1 << ".\t" << movieVec[i].movieID << "\t"
			<< movieVec[i].totalReviews << "\t" << movieVec[i].avgReviewScore 
			<< "\t" << movieVec[i].movieName << endl;
	}
}// end getTop10Movies()

// Passing review vector from main() by reference. Using a vector of a map 
// structure and to store the incrementation of the number of reviews each 
// reviewer gives. This vector of map is then sorted by the number of reviews
// in decending order unless the values are the same and then in ascending order
// of the reviewer ID. 
void getTop10Reviewers ( const vector<review>& reviewVec){

	// Create variable that is key value pair (key is reviewer ID and value is 
	// the number of reviews) called reviewMaps
	map<int, int> reviewMap;

	// Increment each time a reviewer post a review for a movie and store the 
	// count in the map 
	for( auto x : reviewVec){ reviewMap[x.reviewerID]++; }

	// Create a vector composed of the map
	vector<pair<int, int> > mapVector(reviewMap.begin(), reviewMap.end());

	// Sort the pair by the number reviews produced by the reviewer in decending 
	// order and in the instance that the two values are the same sort in 
	// ascending order the reviewer ID.
	sort(mapVector.begin(), mapVector.end(), 
			[](pair<int, int>& m1, pair<int, int>& m2){

			// second refers to number of reviews and first refers to reviewer ID
			return (m1.second == m2.second) ? (m1.first < m2.first) 
											: (m1.second > m2.second);
	});


	// print out results of top 10 reviewers
	cout << "\n>> Top 10 Reviewers <<\n" << endl;
	cout << "Rank\tID\tReviews" << endl;
	for (int i = 0; i < 10; i++){

		cout << i + 1 << "\t" << mapVector[i].first 
		<< "\t" << mapVector[i].second << endl;
	}
} // end getTop10Reviewers()

// Passes vector of movie from main() by reference. User is promted for the 
// movie ID which is limited from 1 to the total number of movies. The vector 
// of movie is resorted in acsending order of movie id number. An error is 
// produced if the user picks a value outside of range of possible movies. Exits
// on input 0.
void getMovieInfo ( vector<movie>& movieVec){
	// initialize total number of movies
	int numMovies = movieVec.size();
	int userInput;

	// Restore movie sort in ascending order of movie id.
	sort(movieVec.begin(), movieVec.end(), [](movie m1, movie m2){
		return( m1.movieID < m2.movieID); 
	});

	// Promt user for movie ID
	cout << "\nPlease enter movie ID [1 ... " << numMovies 
			<< "] , 0 to stop: ";
	cin >> userInput;

	while ( userInput != 0 ){

		if( userInput < 0  || userInput > numMovies ) {
			cout << "ERROR: Invalid movie ID. Please try again..." << endl;
		}
		else{
			cout << "\n>> Movie Information <<\n" << endl;
			movie m  = movieVec[userInput - 1];
			cout << "Movies:\t" << m.movieName << endl;
			cout << "Avg rating:\t" << m.avgReviewScore << endl;
			cout << "Num reviews:\t" << m.totalReviews << endl;
			cout << "Num 1's:\t" << m.scoringRange[0] << endl;
			cout << "Num 2's:\t" << m.scoringRange[1] << endl;
			cout << "Num 3's:\t" << m.scoringRange[2] << endl;
			cout << "Num 4's:\t" << m.scoringRange[3] << endl;
			cout << "Num 5's:\t" << m.scoringRange[4] << endl;
		}

		cout << "Please enter movie ID [1 ... " << numMovies 
			<< "] , 0 to stop: ";
		
		cin >> userInput;
	}
} // end getMovieInfo()

// Parse each line of data from ifstream movie file using getline. Create
// movie instance using the parsed string by pushing the type instance to a 
// vector of movie. 
void readMovieFile( ifstream& movieFile, vector<movie>& movieList){

	string movieString;	// declare string for parsed line

	cout << ">> Reading Movie File <<" << endl;
	// loop through movie data file line by line using getline()
	while ( getline(movieFile, movieString)){
		// Create variable of type movie and pass string
		movie currentMovie(movieString);
		// Push type instance of movie into vector
		movieList.push_back(currentMovie);
	}
} // end readMovieFile()

// Parse each line of data from ifstream movie file using getline. Create
// review instance using the parsed string by pushing the type instance to a 
// vector of review. 
void readReviewFile( ifstream& reviewFile, vector<review>& reviewList){

	string reviewString;	// declare string for parsed line
	
	cout << ">> Reading Review File <<\t" << endl;
	// loop through review data file line by line using getline()
	while (getline(reviewFile, reviewString)){
		// Create variable of type review and pass string
		review currentReview(reviewString);
		// Push type instance of review into vector
		reviewList.push_back(currentReview);
	}
} // end readReviewFile()


int main() {
	
	// Open files:
	ifstream movieFile("movies.txt");
	ifstream reviewFile("reviews.txt");

	// Create vectors of all movies and reviews
	vector<movie> movieList;
	vector<review> reviewList;
	
	/* Read movieFile and reviewFile line by line
	 	and convert each line into a string */
	readMovieFile(movieFile, movieList );
	readReviewFile( reviewFile, reviewList);
	
	getTop10Movies(movieList, reviewList);

	getTop10Reviewers(reviewList);

	getMovieInfo(movieList);
	
	return 0;
}
