//
// BusinessTier:  business logic, acting as interface between UI and data store.
//

using System;
using System.Collections.Generic;
using System.Data;


namespace BusinessTier
{

  //
  // Business:
  //
  public class Business
  {
    //
    // Fields:
    //
    private string _DBFile;
    private DataAccessTier.Data datatier;


    //
    // Constructor:
    //
    public Business(string DatabaseFilename)
    {
      _DBFile = DatabaseFilename;

      datatier = new DataAccessTier.Data(DatabaseFilename);
    }


    //
    // TestConnection:
    //
    // Returns true if we can establish a connection to the database, false if not.
    //
    public bool TestConnection()
    {
      return datatier.TestConnection();
    }

    //
    // GetAllMovies:
    //
    // Retrieves Movie object and returns null if movie is not found.
    //
    public IReadOnlyList<Movie> GetAllMovies()
    {
        List<Movie> movies = new List<Movie>();

        string sql = "Select * from Movies;";

        DataSet ds = datatier.ExecuteNonScalarQuery(sql);

        // Add data to movies list
        if (ds != null)
        {
            DataTable dt = ds.Tables["TABLE"];
            foreach (DataRow row in dt.Rows)
            {
                int MovieID = System.Convert.ToInt32(row["MovieID"]);
                string MovieName = System.Convert.ToString(row["MovieName"]);
                Movie m = new Movie(MovieID, MovieName);
                movies.Add(m);
            }
            return movies;
        }
        else
        {
            return null;
        }

    }// end GetAllMovies();
    
    //
    // GetMovie:
    //
    // Retrieves Movie object based on MOVIE ID; returns null if movie is not
    // found.
    //
    public Movie GetMovie(int MovieID)
    {
        string sql = string.Format("SELECT MovieName FROM Movies WHERE MovieID={0};", MovieID);
        object result = datatier.ExecuteScalarQuery(sql);

        if (result != null)
        {
            string MovieName = System.Convert.ToString(result); ;
            BusinessTier.Movie movie = new Movie(MovieID, MovieName);
            return movie;
            
        }
        else
        {
            return null; 
        }
      
    }// end GetMovie()


    //
    // GetMovie:
    //
    // Retrieves Movie object based on MOVIE NAME; returns null if movie is not
    // found.
    //
    public Movie GetMovie(string MovieName)
    {
      //
      // TODO!
      //
        
        string moviename = MovieName.Replace("'", "''");
        string sql = string.Format("SELECT MovieID FROM Movies WHERE MovieName='{0}';", moviename);
        object result = this.datatier.ExecuteScalarQuery(sql);
        Movie movie;
        if (result != null )
        {
            movie = new Movie(System.Convert.ToInt32(result), MovieName);
            return movie;
        }
        else
        {
            return null;
        }
        
    }


    //
    // AddMovie:
    //
    // Adds the movie, returning a Movie object containing the name and the 
    // movie's id.  If the add failed, null is returned.
    //
    public Movie AddMovie(string MovieName)
    {
      //
      // TODO!
      //
        
        string moviename = MovieName.Replace("'", "''");
        string sql = string.Format(@"INSERT INTO Movies (MovieName) VALUES ('{0}');
                                   SELECT MovieID FROM Movies WHERE MovieID = SCOPE_IDENTITY();", moviename);
        object result = this.datatier.ExecuteScalarQuery(sql);

        Movie movie;
        if (result != null)
        {
            movie = new Movie(System.Convert.ToInt32(result), MovieName);
            return movie;
        }
        else
        {
            return null;
        }
       


    }


    //
    // AddReview:
    //
    // Adds review based on MOVIE ID, returning a Review object containing
    // the review, review's id, etc.  If the add failed, null is returned.
    //
    public Review AddReview(int MovieID, int UserID, int Rating)
    {
      //
      // TODO!
      //
        string sql = string.Format(@"INSERT INTO Reviews (MovieID,UserID,Rating) VALUES ({0},{1},{2});
                                   SELECT ReviewID FROM Reviews WHERE ReviewID = SCOPE_IDENTITY();", MovieID, UserID, Rating);
        object result = datatier.ExecuteScalarQuery(sql);

        if (result != null)
        {
            BusinessTier.Review review = new Review(System.Convert.ToInt32(result), MovieID, UserID, Rating);
            return review;
        }
        else
        {
            return null;
        }

    }


    //
    // GetMovieDetail:
    //
    // Given a MOVIE ID, returns detailed information about this movie --- all
    // the reviews, the total number of reviews, average rating, etc.  If the 
    // movie cannot be found, null is returned.
    //
    public MovieDetail GetMovieDetail(int MovieID)
    {
      //
      // TODO!
      //

        MovieDetail movieDetail;
        Movie movie = this.GetMovie(MovieID);
        if (movie != null)
        {
            // Get number of Reviews
            string str = string.Format("SELECT COUNT(*) FROM Reviews WHERE MovieID={0};", MovieID);
            int numReviews = Convert.ToInt32(this.datatier.ExecuteScalarQuery(str));
            
            // Get Average Rating
            str = string.Format(@"SELECT ROUND(AVG(CAST(Rating AS Float)), 4) 
                                    FROM Reviews WHERE MovieID={0};", MovieID);
            double avgRating = Convert.ToDouble(this.datatier.ExecuteScalarQuery(str));
            List<Review> reviews = new List<Review>();
            
            // Get all reviews by user
            str = string.Format(@"SELECT ReviewID, UserID, Rating             
                                    FROM Reviews             
                                    WHERE MovieID={0}           
                                    ORDER BY Rating Desc, UserID ASC;", MovieID);

            // Create movieDetail object
            foreach (DataRow row in this.datatier.ExecuteNonScalarQuery(str).Tables["TABLE"].Rows)
            {
                Review review = new Review(Convert.ToInt32(row["ReviewID"]), MovieID,
                                    Convert.ToInt32(row["UserID"]), Convert.ToInt32(row["Rating"]));
                reviews.Add(review);
            }
            movieDetail = new MovieDetail(movie, avgRating, numReviews, reviews);
        }
        else
        {
            movieDetail = null;
        }
        return movieDetail;






    }


    //
    // GetUserDetail:
    //
    // Given a USER ID, returns detailed information about this user --- all
    // the reviews submitted by this user, the total number of reviews, average 
    // rating given, etc.  If the user cannot be found, null is returned.
    //
    public UserDetail GetUserDetail(int UserID)
    {
      //
      // TODO!
      //
        string sql;

        // Create user object
        BusinessTier.User user = new User(UserID);

        // Get average rating
        sql = string.Format(@"SELECT ROUND(AVG(CAST(Rating as Float)),4)
                                   FROM Reviews
                                   WHERE UserID = {0};", UserID);
        object avgRatingResult = datatier.ExecuteScalarQuery(sql);

        // Get total number of reviews
        sql = string.Format(@"SELECT COUNT(Rating) as NumRatings
                                    FROM Reviews
                                    WHERE UserID = '{0}';", UserID);
        object numReviewsResult = datatier.ExecuteScalarQuery(sql);

        // Get all reviews by user
        sql = string.Format(@"SELECT * FROM Reviews WHERE MovieID={0} 
                                     ORDER BY Rating DESC, UserID ASC;", UserID);
        DataSet userReviewsResult = datatier.ExecuteNonScalarQuery(sql);

        // Create UserDetail object
        if (avgRatingResult == null || numReviewsResult == null || userReviewsResult == null)
        {
            return null;
        }
        else
        {
            double AvgRating = System.Convert.ToDouble(avgRatingResult);
            int NumReviews = System.Convert.ToInt32(numReviewsResult);
            List<Review> Reviews = new List<Review>();

            DataTable dt = userReviewsResult.Tables["TABLE"];
            foreach (DataRow row in dt.Rows)
            {
                int ReviewID = System.Convert.ToInt32(row["ReviewID"]);
                int MovieID = System.Convert.ToInt32(row["MovieID"]);
                int Rating = System.Convert.ToInt32(row["Rating"]);
                Review review = new Review(ReviewID, MovieID, UserID, Rating);
                Reviews.Add(review);
            }

            BusinessTier.UserDetail userDetail = new UserDetail(user, AvgRating, NumReviews, Reviews);
            return userDetail;
        }
    }


    //
    // GetTopMoviesByAvgRating:
    //
    // Returns the top N movies in descending order by average rating.  If two
    // movies have the same rating, the movies are presented in ascending order
    // by name.  If N < 1, an EMPTY LIST is returned.
    //
    public IReadOnlyList<Movie> GetTopMoviesByAvgRating(int N)
    {
      List<Movie> movies = new List<Movie>();

      //
      // TODO!
      //

      string sql = string.Format(@"SELECT TOP {0} Movies.MovieID, Movies.MovieName FROM Movies
                                    INNER JOIN (SELECT MovieID, ROUND(AVG(CAST(Rating AS Float)), 4) as AvgRating
                                    FROM Reviews GROUP BY MovieID) TEMP
                                    ON TEMP.MovieID = Movies.MovieID
                                    ORDER BY TEMP.AvgRating DESC, Movies.MovieName ASC;", N);

      DataSet ds = datatier.ExecuteNonScalarQuery(sql);

      // Add data to movies list
      if (ds != null)
      {
          DataTable dt = ds.Tables["TABLE"];
          foreach (DataRow row in dt.Rows)
          {
              int MovieID = System.Convert.ToInt32(row["MovieID"]);
              string MovieName = System.Convert.ToString(row["MovieName"]);
              Movie movie = new Movie(MovieID, MovieName);
              movies.Add(movie);
          }
          return movies;
      }
      else
      {
          return null;
      }
      
    }


    //
    // GetTopMoviesByNumReviews
    //
    // Returns the top N movies in descending order by number of reviews.  If two
    // movies have the same number of reviews, the movies are presented in ascending
    // order by name.  If N < 1, an EMPTY LIST is returned.
    //
    public IReadOnlyList<Movie> GetTopMoviesByNumReviews(int N)
    {
      List<Movie> movies = new List<Movie>();

      //
      // TODO!
      //
      string sql = string.Format(@"SELECT TOP {0} Movies.MovieID, Movies.MovieName
                                    FROM Movies
                                    INNER JOIN (SELECT MovieID, COUNT(*) as RatingCount FROM Reviews
                                    GROUP BY MovieID) TEMP
                                    ON TEMP.MovieID = Movies.MovieID
                                    ORDER BY TEMP.RatingCount DESC, Movies.MovieName ASC;", N);

      DataSet ds = datatier.ExecuteNonScalarQuery(sql);

      // Add data to movies list
      if (ds != null)
      {
          DataTable dt = ds.Tables["TABLE"];
          foreach (DataRow row in dt.Rows)
          {
              int MovieID = System.Convert.ToInt32(row["MovieID"]);
              string MovieName = System.Convert.ToString(row["MovieName"]);
              Movie movie = new Movie(MovieID, MovieName);
              movies.Add(movie);
          }
          return movies;  
      }
      else
      {
          return null;
      }
    }


    //
    // GetTopUsersByNumReviews
    //
    // Returns the top N users in descending order by number of reviews.  If two
    // users have the same number of reviews, the users are presented in ascending
    // order by user id.  If N < 1, an EMPTY LIST is returned.
    //
    public IReadOnlyList<User> GetTopUsersByNumReviews(int N)
    {
      List<User> users = new List<User>();

      //
      // TODO!
      //
      string sql = string.Format(@"SELECT TOP {0} UserID, COUNT(*) AS RatingCount
                                    FROM Reviews GROUP BY UserID
                                    ORDER BY RatingCount DESC, UserID ASC;", N);

      DataSet ds = datatier.ExecuteNonScalarQuery(sql);

      // Add data to movies list
      if (ds != null)
      {
          DataTable dt = ds.Tables["TABLE"];
          foreach (DataRow row in dt.Rows)
          {
              int UserID = System.Convert.ToInt32(row["UserID"]);
              User u = new User(UserID);
              users.Add(u);
          }
          return users;
      }
      else
      {
          return null;
      }

    }

  }//class

}//namespace
