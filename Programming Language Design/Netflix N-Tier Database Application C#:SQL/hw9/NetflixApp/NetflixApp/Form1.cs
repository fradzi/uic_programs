/*
 * Netflix Database Application using N-Tier Design.
 * 
 * Filip Radzikowski
 * U. of Illinois, Chicago
 * CS341, Spring 2015
 * HW9
 * 
 **/



using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;


namespace NetflixApp
{
  public partial class Form1 : Form
  {
    //
    // Class members:
    //
    private Random RandomNumberGenerator;

    //
    // Constructor:
    //
    public Form1()
    {
      InitializeComponent();

      RandomNumberGenerator = new Random();
    }

    private void Form1_Load(object sender, EventArgs e)
    {

    }

    

    /***********************************************************************************************/
    //
    // Test Connection:
    //
    private void cmdConnect_Click(object sender, EventArgs e)
    {
      try
      {
        string filename, connectionInfo;
        SqlConnection db;

        filename = this.txtFileName.Text;
        connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

        db = new SqlConnection(connectionInfo);
        db.Open();

        string msg = db.State.ToString();
        MessageBox.Show(msg);

        db.Close();
      }
      catch (Exception ex)
      {
        MessageBox.Show("Error: " + ex.Message);
      }
    }




    /***********************************************************************************************/
    //
    // Get Movie Reviews: from id...
    //
    private void cmdGetMovieReviews_Click(object sender, EventArgs e)
    {

        listBox1.Items.Clear();

        int mID = System.Convert.ToInt32(txtMovieID.Text);

        BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");

        BusinessTier.Movie moviename = BT.GetMovie(mID);
        if (moviename == null)
        {
            listBox1.Items.Add("Movie does not exist");
            return;
        }
        //Display movie name
        listBox1.Items.Add(moviename.MovieName);

        BusinessTier.MovieDetail movieDetail = BT.GetMovieDetail(mID);

        if (movieDetail == null)
        {
            listBox1.Items.Add("** ERROR **");
        }
        else
        {
            foreach (var m in movieDetail.Reviews)
            {
                listBox1.Items.Add(m.ReviewID + " : " + m.Rating);
            }

        }





//      listBox1.Items.Clear();

//      string filename, connectionInfo;
//      SqlConnection db;

//      filename = this.txtFileName.Text;
//      connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

//      db = new SqlConnection(connectionInfo);
//      db.Open();

//      SqlCommand cmd = new SqlCommand();
//      cmd.Connection = db;

//      cmd.CommandText = string.Format("SELECT MovieName FROM Movies WHERE MovieID={0};",
//        txtMovieID.Text);

//      //MessageBox.Show(cmd.CommandText);

//      object result = cmd.ExecuteScalar();

//      if (result == null || result.ToString() == "")
//      {
//        listBox1.Items.Add("Movie not found...");
//      }
//      else
//      {
//        //
//        // get the reviews:
//        //

//        listBox1.Items.Add(result.ToString());

//        SqlDataAdapter adapter = new SqlDataAdapter(cmd);
//        DataSet ds = new DataSet();

//        cmd.CommandText = "SELECT UserID, Rating FROM Reviews WHERE MovieID = " + txtMovieID.Text + ";";
//        cmd.CommandText = string.Format(@"SELECT UserID, Rating 
//            FROM Reviews 
//            WHERE MovieID={0}
//            ORDER BY Rating Desc, UserID ASC;",
//          txtMovieID.Text);

//        //MessageBox.Show(cmd.CommandText);

//        adapter.Fill(ds);

//        DataTable dt = ds.Tables["TABLE"];

//        if (dt.Rows.Count == 0)
//        {
//          listBox1.Items.Add("No reviews...");
//        }
//        else
//        {
//          foreach (DataRow row in dt.Rows)
//            listBox1.Items.Add(row["UserID"] + ": " + row["Rating"]);
//        }
//      }//else

//      db.Close();
    }



    /***********************************************************************************************/
    //
    // Average Rating:
    //
    private void cmdAvgRating_Click(object sender, EventArgs e)
    {


        listBox1.Items.Clear();

        string name = txtRatingsMovieName.Text;

        BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");

        BusinessTier.Movie movie = BT.GetMovie(name);
        if (movie == null)
        {
            listBox1.Items.Add("Movie does not exist");
            return;
        }

        BusinessTier.MovieDetail movieDetail = BT.GetMovieDetail(movie.MovieID);

        if (movieDetail == null)
        {
            listBox1.Items.Add("** ERROR **");
        }
        else
        {

            listBox1.Items.Add("Average Rating : " + movieDetail.AvgRating);

        }



//      listBox1.Items.Clear();

//      string filename, connectionInfo;
//      SqlConnection db;

//      filename = this.txtFileName.Text;
//      connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

//      db = new SqlConnection(connectionInfo);
//      db.Open();

//      //
//      // Compute average rating:
//      //
//      string name = txtRatingsMovieName.Text;
//      name = name.Replace("'", "''");  // escape any single ' in the string:

//      SqlCommand cmd = new SqlCommand();
//      cmd.Connection = db;

//      cmd.CommandText = string.Format(@"SELECT ROUND(AVG(CAST(Rating AS Float)), 4) AS AvgRating 
//          FROM Reviews
//          INNER JOIN Movies ON Reviews.MovieID = Movies.MovieID
//          WHERE Movies.MovieName='{0}';", 
//        name);

//      //MessageBox.Show(cmd.CommandText);

//      object result = cmd.ExecuteScalar();

//      db.Close();

//      if (result == null || result.ToString() == "")
//      {
//        listBox1.Items.Add("Movie not found...");
//      }
//      else
//      {
//        listBox1.Items.Add("Average rating: " + result.ToString());
//      }
    }





    /***********************************************************************************************/
    //
    // Each Rating:
    //
    private void cmdEachRating_Click(object sender, EventArgs e)
    {


        listBox1.Items.Clear();

        string name = txtRatingsMovieName.Text;
        
        BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");

        BusinessTier.Movie movie = BT.GetMovie(name); 
        if (movie == null)
        {
            listBox1.Items.Add("Movie does not exist");
            return;
        }
        
        BusinessTier.MovieDetail movieDetail = BT.GetMovieDetail(movie.MovieID);

        if (movieDetail == null)
        {
            listBox1.Items.Add("** No Ratings **");
        }
        else
        {

            int[] count = {0,0,0,0,0}; 
            
            foreach (var r in movieDetail.Reviews)
            {
                count[r.Rating - 1]++;
            }

            //display
            for (int i = 5; i > 0; i--)
            {
                listBox1.Items.Add( i + " : " + count[i - 1]);
            }

            listBox1.Items.Add("Total : " + movieDetail.NumReviews);
            
        }
        
        
//      listBox1.Items.Clear();

//      string filename, connectionInfo;
//      SqlConnection db;

//      filename = this.txtFileName.Text;
//      connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

//      db = new SqlConnection(connectionInfo);
//      db.Open();

//      SqlCommand cmd = new SqlCommand();
//      cmd.Connection = db;

//      //
//      // Group all the ratings for given movie, and then count each group:
//      //
//      string name = txtRatingsMovieName.Text;
//      name = name.Replace("'", "''");  // escape any single ' in the string:

//      cmd.CommandText = string.Format(@"SELECT Rating, COUNT(Rating) as RatingCount
//          FROM Reviews
//          INNER JOIN Movies ON Reviews.MovieID = Movies.MovieID
//          WHERE Movies.MovieName='{0}'
//          GROUP BY Rating
//          ORDER BY Rating DESC;",
//        name);

//      //MessageBox.Show(cmd.CommandText);

//      SqlDataAdapter adapter = new SqlDataAdapter(cmd);
//      DataSet ds = new DataSet();

//      adapter.Fill(ds);  // execute!

//      db.Close();

//      //
//      // display results:
//      //
//      int total = 0;

//      DataTable dt = ds.Tables["TABLE"];

//      if (dt.Rows.Count == 0)
//      {
//        listBox1.Items.Add("Movie not found...");
//      }
//      else
//      {
//        //
//        // we have ratings data, display:
//        //
//        foreach (DataRow row in dt.Rows)
//        {
//          listBox1.Items.Add(row["Rating"] + ": " + row["RatingCount"]);

//          total = total + Convert.ToInt32(row["RatingCount"]);
//        }

//        listBox1.Items.Add("Total: " + total.ToString());
//      }
    }




    /***********************************************************************************************/
    //
    // Add movie:
    //
    private void cmdInsertMovie_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();

      BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");
      BusinessTier.Movie movie = BT.AddMovie(this.txtInsertMovieName.Text);

      if (movie != null)
      {
          listBox1.Items.Add("Success, movie id" + movie.MovieID.ToString() + "added.");

      }
      else
      {
          listBox1.Items.Add("** Insert failed?! **");
      }

            
      //string filename, connectionInfo;
      //SqlConnection db;

      //filename = this.txtFileName.Text;
      //connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

      //db = new SqlConnection(connectionInfo);
      //db.Open();

      //SqlCommand cmd = new SqlCommand();
      //cmd.Connection = db;
      
      ////
      //// insert movie:
      ////
      //string name = txtInsertMovieName.Text;
      //name = name.Replace("'", "''");  // escape any single ' in the string:

      //cmd.CommandText = string.Format("INSERT INTO Movies(MovieName) Values('{0}');",
      //  name);

      ////MessageBox.Show(cmd.CommandText);

      //int rowsModified = cmd.ExecuteNonQuery();

      //
      // display results:
      //
      //listBox1.Items.Add("Rows modified: " + rowsModified.ToString());

      //if (rowsModified == 1) // success!
      //{
      //  listBox1.Items.Add("Success, movie added.");
      //}
      //else
      //{
      //  listBox1.Items.Add("** Insert failed?! **");
      //}
    }



    /***********************************************************************************************/
    private void tbarRating_Scroll(object sender, EventArgs e)
    {
      lblRating.Text = tbarRating.Value.ToString();
    }




    /***********************************************************************************************/
    //
    // Add Review:
    //
    private void cmdInsertReview_Click(object sender, EventArgs e)
    {

        listBox1.Items.Clear();

        string name = txtInsertMovieName.Text;
        name = name.Replace("'", "''");  // escape any single ' in the string:

        BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");

        BusinessTier.Movie movie = BT.GetMovie(name);

        BusinessTier.Review review = BT.AddReview(movie.MovieID, 123, tbarRating.Value);

        if (name != null)
        {
            listBox1.Items.Add("Success, movie reviewer " + review.ReviewID.ToString());
            listBox1.Items.Add("added review of " + review.Rating.ToString());


        }
        else
        {
            listBox1.Items.Add("** Insert failed?! **");
        }




      //listBox1.Items.Clear();

      //string filename, connectionInfo;
      //SqlConnection db;

      //filename = this.txtFileName.Text;
      //connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

      //db = new SqlConnection(connectionInfo);
      //db.Open();

      //SqlCommand cmd = new SqlCommand();
      //cmd.Connection = db;

      ////
      //// first we need to lookup the movie id:
      ////
      //string name = txtInsertMovieName.Text;
      //name = name.Replace("'", "''");  // escape any single ' in the string:

      //cmd.CommandText = string.Format("SELECT MovieID FROM Movies WHERE MovieName='{0}';",
      //  name);

      ////MessageBox.Show(cmd.CommandText);
      
      //object result = cmd.ExecuteScalar();

      //if (result == null || result.ToString() == "")
      //{
      //  listBox1.Items.Add("Movie not found...");
      //}
      //else
      //{
      //  //
      //  // Found movie, so now we can insert movie review:
      //  //
      //  int movieid = Convert.ToInt32(result);
      //  int userid = RandomNumberGenerator.Next(100000, 999999);  // 6-digit user ids:

      //  //
      //  // now insert review:
      //  //
      //  cmd.CommandText = string.Format("INSERT INTO Reviews(MovieID, UserID, Rating) Values({0}, {1}, {2});",
      //    movieid,
      //    userid,
      //    lblRating.Text);

      //  //MessageBox.Show(cmd.CommandText);

      //  int rowsModified = cmd.ExecuteNonQuery();

      //  //
      //  // display results:
      //  //
      //  listBox1.Items.Add("Rows modified: " + rowsModified.ToString());

      //  if (rowsModified == 1) // success!
      //  {
      //    listBox1.Items.Add("Success, review added.");
      //  }
      //  else
      //  {
      //    listBox1.Items.Add("** Insert failed?! **");
      //  }
      //}
    }


    /***********************************************************************************************/
    //
    // Top N Movies by Average Rating:
    //
    private void cmdTopMoviesByAvgRating_Click(object sender, EventArgs e)
    {
      listBox1.Items.Clear();

      BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");
      int N = System.Convert.ToInt32(this.txtTopN.Text);

      IReadOnlyList<BusinessTier.Movie> movies = BT.GetTopMoviesByAvgRating(N);

      if (movies.Count == 0)
      { // failed somehow..
          listBox1.Items.Add("**ErrorBlinkStyle, OrderedEnumerableRowCollection database is empty?!");
      }
      else
      {
          foreach (BusinessTier.Movie m in movies)
          {
              BusinessTier.MovieDetail details = BT.GetMovieDetail(m.MovieID);

              listBox1.Items.Add(m.MovieName + ": " + details.AvgRating);
          }
      }



//      string filename, connectionInfo;
//      SqlConnection db;

//      filename = this.txtFileName.Text;
//      connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

//      db = new SqlConnection(connectionInfo);
//      db.Open();

//      SqlCommand cmd = new SqlCommand();
//      cmd.Connection = db;

//      //
//      // Group all the reviews for each movie, compute averages, and take top N:
//      //
//      string N = txtTopN.Text;

//      cmd.CommandText = string.Format(@"SELECT TOP {0} Movies.MovieName, g.AvgRating 
//            FROM Movies
//            INNER JOIN 
//              (
//                SELECT MovieID, ROUND(AVG(CAST(Rating AS Float)), 4) as AvgRating 
//                FROM Reviews
//                GROUP BY MovieID
//              ) g
//            ON g.MovieID = Movies.MovieID
//            ORDER BY g.AvgRating DESC, Movies.MovieName Asc;",
//        N);

//      //MessageBox.Show(cmd.CommandText);

//      SqlDataAdapter adapter = new SqlDataAdapter(cmd);
//      DataSet ds = new DataSet();

//      adapter.Fill(ds);  // execute!

//      db.Close();

      ////
      //// display results:
      ////
      //DataTable dt = ds.Tables["TABLE"];

      //if (dt.Rows.Count == 0)
      //{
      //  listBox1.Items.Add("**Error, or database is empty?!");
      //}
      //else
      //{
      //  //
      //  // we have ratings data, display:
      //  //
      //  foreach (DataRow row in dt.Rows)
      //    listBox1.Items.Add(row["MovieName"] + ": " + row["AvgRating"]);
      //}
    }



    /***********************************************************************************************/
    //
    // Top N Movies by # of reviews:
    //
    private void cmdTopMoviesByNumReviews_Click(object sender, EventArgs e)
    {

        listBox1.Items.Clear();

        BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");
        int N = System.Convert.ToInt32(this.txtTopN.Text);

        IReadOnlyList<BusinessTier.Movie> movies = BT.GetTopMoviesByNumReviews(N);

        if (movies.Count == 0)
        { // failed somehow..
            listBox1.Items.Add("**ErrorBlinkStyle, OrderedEnumerableRowCollection database is empty?!");
        }
        else
        {
            foreach (BusinessTier.Movie m in movies)
            {
                BusinessTier.MovieDetail details = BT.GetMovieDetail(m.MovieID);

                listBox1.Items.Add(m.MovieName + ": " + details.AvgRating);
            }
        }     




//        listBox1.Items.Clear();

//        string filename, connectionInfo;
//        SqlConnection db;

//        filename = this.txtFileName.Text;
//        connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

//        db = new SqlConnection(connectionInfo);
//        db.Open();

//        SqlCommand cmd = new SqlCommand();
//        cmd.Connection = db;

//        //
//        // Group all the reviews for each movie, compute averages, and take top N:
//        //
//        string N = txtTopN.Text;

//        cmd.CommandText = string.Format(@"SELECT TOP {0} Movies.MovieName, g.RatingCount 
//            FROM Movies
//            INNER JOIN 
//              (
//                SELECT MovieID, COUNT(*) as RatingCount 
//                FROM Reviews
//                GROUP BY MovieID
//              ) g
//            ON g.MovieID = Movies.MovieID
//            ORDER BY g.RatingCount DESC, Movies.MovieName Asc;",
//          N);

//        //MessageBox.Show(cmd.CommandText);

//        SqlDataAdapter adapter = new SqlDataAdapter(cmd);
//        DataSet ds = new DataSet();

//        adapter.Fill(ds);  // execute!

//        db.Close();

//        //
//        // display results:
//        //
//        DataTable dt = ds.Tables["TABLE"];

//        if (dt.Rows.Count == 0)
//        {
//            listBox1.Items.Add("**Error, or database is empty?!");
//        }
//        else
//        {
//            //
//            // we have ratings data, display:
//            //
//            foreach (DataRow row in dt.Rows)
//                listBox1.Items.Add(row["MovieName"] + ": " + row["RatingCount"]);
//        }
    }




    /***********************************************************************************************/
    //
    // Top N Users by # of reviews:
    //
    private void cmdTopUsers_Click(object sender, EventArgs e)
    {

      
        listBox1.Items.Clear();

        BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");
        int N = System.Convert.ToInt32(this.txtTopN.Text);

        IReadOnlyList<BusinessTier.User> users = BT.GetTopUsersByNumReviews(N);

        if (users.Count == 0)
        { // failed somehow..
            listBox1.Items.Add("**ErrorBlinkStyle, OrderedEnumerableRowCollection database is empty?!");
        }
        else
        {
            foreach (BusinessTier.User m in users)
            {
                BusinessTier.UserDetail details = BT.GetUserDetail(m.UserID); //BT.GetMovieDetail(m.MovieID);

                listBox1.Items.Add(m.UserID + ": " + details.NumReviews);
            }
        }     
        
        
        
        
        
//      listBox1.Items.Clear();

//      string filename, connectionInfo;
//      SqlConnection db;

//      filename = this.txtFileName.Text;
//      connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

//      db = new SqlConnection(connectionInfo);
//      db.Open();

//      SqlCommand cmd = new SqlCommand();
//      cmd.Connection = db;

//      //
//      // Group all the reivews by user, count, and take top N:
//      //
//      string N = txtTopN.Text;

//      cmd.CommandText = string.Format(@"SELECT TOP {0} UserID, COUNT(*) AS RatingCount
//            FROM Reviews
//            GROUP BY UserID
//            ORDER BY RatingCount DESC, UserID Asc;",
//        N);

//      //MessageBox.Show(cmd.CommandText);

//      SqlDataAdapter adapter = new SqlDataAdapter(cmd);
//      DataSet ds = new DataSet();

//      adapter.Fill(ds);  // execute!

//      db.Close();

//      //
//      // display results:
//      //
//      DataTable dt = ds.Tables["TABLE"];

//      if (dt.Rows.Count == 0)
//      {
//        listBox1.Items.Add("**Error, or database is empty?!");
//      }
//      else
//      {
//        //
//        // we have ratings data, display:
//        //
//        foreach (DataRow row in dt.Rows)
//          listBox1.Items.Add(row["UserID"] + ": " + row["RatingCount"]);
//      }
    }




    /***********************************************************************************************/
    private void cmdAllMovies_Click(object sender, EventArgs e)
    {

        // Clear listbox of previous output
        this.listBox1.Items.Clear();
        BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");
        IReadOnlyList<BusinessTier.Movie> movies = BT.GetAllMovies();

        if (movies.Count == 0)
        {
            this.listBox1.Items.Add("Unable to get All Movies.");
            return;
        }

        string msg;
        foreach (var movie in movies)
        {
            this.listBox1.Items.Add(movie.MovieID + " " + movie.MovieName);
        }




    //  listBox1.Items.Clear();

    //  string filename, connectionInfo;
    //  SqlConnection db;

    //  filename = this.txtFileName.Text;
    //  connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);

    //  db = new SqlConnection(connectionInfo);
    //  db.Open();

    //  SqlCommand cmd = new SqlCommand();
    //  cmd.Connection = db;

    //  //
    //  // Select all movies, sorted by name ASC:
    //  //
    //  cmd.CommandText = string.Format("SELECT MovieID, MovieName FROM Movies ORDER BY MovieName ASC;");

    //  // MessageBox.Show(cmd.CommandText);

    //  SqlDataAdapter adapter = new SqlDataAdapter(cmd);
    //  DataSet ds = new DataSet();

    //  adapter.Fill(ds);  // execute!

    //  db.Close();

    //  //
    //  // display results:
    //  //
    //  DataTable dt = ds.Tables["TABLE"];

    //  if (dt.Rows.Count == 0)
    //  {
    //    listBox1.Items.Add("**Error, or database is empty?!");
    //  }
    //  else
    //  {
    //    //
    //    // we have ratings data, display:
    //    //
    //    foreach (DataRow row in dt.Rows)
    //      listBox1.Items.Add(row["MovieID"].ToString() + ": " + row["MovieName"].ToString());
    //  }
    }

    private void buttonClick_getMovieName(object sender, EventArgs e)
    {
        listBox1.Items.Clear();

        int mID = System.Convert.ToInt32(txtMovieID.Text);

        BusinessTier.Business BT = new BusinessTier.Business("netflix.mdf");

        BusinessTier.Movie moviename = BT.GetMovie(mID);
        if (moviename == null)
        {
            listBox1.Items.Add("Movie does not exist");
            return;
        }
        //Display movie name
        listBox1.Items.Add(moviename.MovieName);
    }

  }//class
}//namespace
