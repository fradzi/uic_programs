//
// Netflix Database Application
//
// Filip Radzikowski
// U. of Illinois, Chicago
// CS341, Spring 2015
// Homework 8
//



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

namespace hw8
{
    public partial class Form1 : Form
    {

        // Global fields that get repeated in multiple methods
        string filename, connectionInfo;
        SqlConnection db;
        SqlCommand cmd;
        
        
        public Form1()
        {
            InitializeComponent();
            filename = "netflix.mdf"; 
            connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;
                            AttachDbFilename=|DataDirectory|\{0};
                            Integrated Security=True;", filename); 
            db = new SqlConnection(connectionInfo);
        }// end Form1()

        private void Form1_Load(object sender, EventArgs e)
        {

        }// end Form1_Load()

        /**
         * The trackBar limits the user to 5 reviews 1-5
         */
        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            this.label1.Text = this.trackBar1.Value.ToString();
        }// end trackBar1_Scroll()

        /**
         * Displays all movies in the database when user clicks on 
         * getAllmovies button.
         */
        private void getAllmovies_Click(object sender, EventArgs e)
        {
            // clear out listbox from previous items
            displayListBox.Items.Clear();

            // open dataBase
            db.Open();

            string sql, msg; 
            //Query for all movies and order in alphabetical order
            sql = String.Format("select * From Movies ORDER BY MovieName Asc;"); 
            
            // new instance of stored procedure to execute query
            cmd = new SqlCommand(); 
            cmd.Connection = db;    // connect to the dataBase
            cmd.CommandText = sql;  // set statement to execute at data source

            // instance of data commands and database connections used to fill DataSet
            // and update server database
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);
            db.Close();
            
            DataTable dt = ds.Tables["TABLE"];

            // iterate through each row and display contents
            foreach (DataRow row in dt.Rows)
            {
                msg = String.Format("{0}:\t {1}", row["MovieID"].ToString(), row["MovieName"].ToString());
                displayListBox.Items.Add(msg);

            }
           

        }// end getAllMovies_Click()

        /**
         * If movieID exists then all the reviews will be displayed in the 
         * display list box
         */
        private void getReviews_Click(object sender, EventArgs e)
        {

            // check if no input 
            if (this.textBox5.Text.Trim() == "")
            {
                MessageBox.Show("Need to input a MovieID");
                return;
            } 
            
            // clear previous display
            displayListBox.Items.Clear(); 
            db.Open();
            string sql, msg, currentID;
            object result;
            currentID = this.textBox5.Text;

            // query for existing movie name
            sql = string.Format("select MovieName from Movies where MovieID = {0};", System.Convert.ToInt32(currentID));
            
            cmd = new SqlCommand();
            cmd.Connection = db;
            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();
            
            if( result == null)
            {
                db.Close();
                MessageBox.Show("MovieID does not exist for " + currentID);
                return;
            }
            
            // Print the Current name of the movie for review
            displayListBox.Items.Add(result.ToString());
            // query for all reviews and userID
            sql = string.Format("select UserID, Rating from Reviews where MovieID = {0} ORDER BY Rating Desc, UserID Asc;",
                                                                                     System.Convert.ToInt32(currentID));
            cmd.CommandText = sql;

            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);
            db.Close();

            DataTable dt = ds.Tables["TABLE"];

            foreach (DataRow row in dt.Rows)
            {
                msg = string.Format("{0}:\t {1}", row["UserID"].ToString(), row["Rating"].ToString());
                displayListBox.Items.Add(msg);

            }


        }// end getReviews_Click()

        /**
         * When movie is typed and insert movie button is clicked then
         * the new movie is inserted into the database.
         */
        private void insertMovie_Click(object sender, EventArgs e)
        {
            if (this.textBox2.Text.Trim() == "")
            {
                MessageBox.Show("Cannot insert 'empty' MovieName");
                return;
            }


            db.Open();
            string sql, currMovieInput;
            object result;
            currMovieInput = this.textBox2.Text;

            // replaceing a single quote with two single quotes 
            currMovieInput = currMovieInput.Replace("'", "''");

            sql = string.Format("insert into Movies(MovieName) values ('{0}');", currMovieInput );

            cmd = new SqlCommand();
            cmd.Connection = db;
            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            sql = string.Format("select MovieName from Movies where MovieName = '{0}';", currMovieInput);
            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            if (result == null)
            {
                db.Close();
                MessageBox.Show("The Movie failed to insert.");
                return;
            }

            MessageBox.Show("Successfully inserted " + currMovieInput);

            db.Close();

        }// end insertMovie_Click()

        /**
         * When insert reviews button clicked then new review is inserted into
         * selected movie if exists
         */
        private void insertReviews_Click(object sender, EventArgs e)
        {
            // check if the textBox has no input
            if (this.textBox2.Text.Trim() == "")
            {
                MessageBox.Show("Cannot insert 'empty' MovieName");
                return;
            }

            db.Open();
            string sql, currReviewMovie;
            object result;
            currReviewMovie = this.textBox2.Text;

            // replaceing a single quote with two single quotes 
            currReviewMovie = currReviewMovie.Replace("'", "''");

            //query to check if movie exists
            sql = string.Format("select MovieID from Movies where MovieName = '{0}';", currReviewMovie);

            cmd = new SqlCommand();
            cmd.Connection = db;
            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            if (result == null)
            {
                db.Close();
                MessageBox.Show("The movie does not exist");
                return;
            }

            //query to insert new review into movie
            sql = string.Format("insert into Reviews(MovieID, UserID, Rating) values({0} , 1010 , {1});",
                                                        System.Convert.ToInt32(result), System.Convert.ToInt32(trackBar1.Value));
            cmd.CommandText = sql;
            
            // will return how many rows were affected
            int count = cmd.ExecuteNonQuery();
            // if less then 1 then no rows were affected
            if (count < 1)
            {
                db.Close();
                MessageBox.Show("The Review failed to insert.");
                return;
            }

            MessageBox.Show("Successfully inserted review.");
            db.Close();

        }// end insertReviews_Click()
        
        /**
         * When average rating button clicked then the information is displayed
         * in the display list box.
         */
        private void avgRating_Click(object sender, EventArgs e)
        {

            displayListBox.Items.Clear();
            if (this.textBox3.Text.Trim() == "")
            {
                MessageBox.Show("Cannot insert 'empty' MovieName");
                return;
            }

            db.Open();
            string sql, msg, currReviewMovie;
            object result;
            currReviewMovie = this.textBox3.Text;

            sql = string.Format("select MovieID from Movies where MovieName = '{0}';", currReviewMovie);

            cmd = new SqlCommand();
            cmd.Connection = db;
            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            if (result == null)
            {
                db.Close();
                MessageBox.Show("The movie does not exist");
                return;
            }

            sql = string.Format(@"select round(avg(cast(Reviews.Rating as float)),4)
                                    from Reviews
                                    inner join Movies
                                    on Movies.MovieID = Reviews.MovieID
                                    where Movies.MovieName = '{0}';",
                                    currReviewMovie);
                
                
                
            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            db.Close();

            msg = string.Format("'{0}' average rating is : {1}", currReviewMovie, result);
            displayListBox.Items.Add(msg);

        }// end avgRating_Click()

        /**
         * Displays number of ratings for each rating value
         */
        private void eachRating_Click(object sender, EventArgs e)
        {
            displayListBox.Items.Clear();

            if (this.textBox3.Text.Trim() == "")
            {
                MessageBox.Show("Cannot insert 'empty' MovieName");
                return;
            }

            db.Open();
            string sql, msg, currMovie;
            object result;

            currMovie = this.textBox3.Text;

            // replaceing a single quote with two single quotes 
            currMovie = currMovie.Replace("'", "''");

            sql = string.Format("select MovieName from Movies where MovieName = '{0}'", currMovie);

            cmd = new SqlCommand();
            cmd.Connection = db;
            cmd.CommandText = sql;

            result = cmd.ExecuteScalar();

            if (result == null)
            {
                db.Close();
                MessageBox.Show("The Movie {0} does not exist.", currMovie);
                return;
            }

            sql = string.Format(@"select distinct Reviews.Rating as CurrRating, count(Reviews.Rating) as RatingCount
                                    from Reviews
                                    inner join Movies
                                    on Movies.MovieID = Reviews.MovieID
                                    where Movies.MovieName = '{0}'
                                    group by Reviews.Rating 
                                    ORDER BY Reviews.Rating desc;", currMovie);

            cmd.CommandText = sql;
     
            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);
            
            DataTable dt = ds.Tables["TABLE"];
            
            displayListBox.Items.Add(string.Format("Rating\tCount"));
            foreach (DataRow row in dt.Rows)
            {
                msg = string.Format("{0}:\t {1}", row["CurrRating"].ToString(), row["RatingCount"].ToString());
                displayListBox.Items.Add(msg);

            }

            //get the total number of reviews
            sql = string.Format(@"select count(Reviews.Rating) 
                                    from Reviews
                                    inner join Movies
                                    on Reviews.MovieID = Movies.MovieID
                                    where MovieName = '{0}'",
                                    currMovie);

            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();
            db.Close();
            msg = string.Format("Total:\t{0}", result);
            displayListBox.Items.Add(msg);
        
        }// end eachRating_Click()
    
        /**
         * Top N movies by average rating are displayed in display list box
         */
        private void nMoviesAvgRating_Click(object sender, EventArgs e)
        {
            displayListBox.Items.Clear();

            if (this.textBox4.Text.Trim() == "")
            {
                MessageBox.Show("Cannot insert 'empty' Number of Movies");
                return;
            }

            db.Open();
            string msg, sql, N;
            object result;

            N = this.textBox4.Text;

            
            sql = string.Format("select count(MovieName) from Movies");
            cmd = new SqlCommand();
            cmd.Connection = db;
            cmd.CommandText = sql;
            
            result = cmd.ExecuteScalar();

            // handle if user enter N larger than available rows
            if (System.Convert.ToInt32(N) > System.Convert.ToInt32(result))
            {    
                MessageBox.Show("Cant display more Movies than there are. Will display max number of movies.");
                N = result.ToString();
            }

            sql = string.Format(@"select top {0} Movies.MovieName, round(avg(cast(Reviews.Rating as float)), 4) as AvgReviews 
                                    from Reviews
                                    inner join Movies
                                    on Movies.MovieID = Reviews.MovieID
                                    group by Movies.MovieName 
                                    order by  round(avg(cast(Reviews.Rating as float)), 4) desc, Movies.MovieName asc;",
                                    System.Convert.ToInt32(N));
         
            
            cmd.CommandText = sql;
            db.Close();

            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);

            DataTable dt = ds.Tables["TABLE"];

            foreach (DataRow row in dt.Rows)
            {
                msg = string.Format("{0}: {1}", row["MovieName"].ToString(), row["AvgReviews"].ToString());
                displayListBox.Items.Add(msg);

            }
            
        }// nMoviesAvgRating_Click()

        /**
         * Top N movies by number of reviews are displayed in display list box
         */
        private void nMoviesNumReviews_Click(object sender, EventArgs e)
        {
            displayListBox.Items.Clear();

            if (this.textBox4.Text.Trim() == "")
            {
                MessageBox.Show("Cannot insert 'empty' Number of Movies");
                return;
            }

            db.Open();
            string msg, sql, N;
            object result;

            N = this.textBox4.Text;


            sql = string.Format("select count(MovieName) from Movies");
            cmd = new SqlCommand();
            cmd.Connection = db;
            cmd.CommandText = sql;

            result = cmd.ExecuteScalar();

            // handle if user enter N larger than available rows
            if (System.Convert.ToInt32(N) > System.Convert.ToInt32(result))
            {
                MessageBox.Show("Cant display more Movies than there are. Will display max number of movies.");
                N = result.ToString();
            }

            sql = string.Format(@"select top {0} Movies.MovieName, count(Reviews.Rating) as NumberOfReviews
                                    from Reviews
                                    inner join Movies
                                    on Movies.MovieID = Reviews.MovieID
                                    group by Movies.MovieName
                                    order by count(Reviews.Rating) desc, Movies.MovieName asc;",
                                    System.Convert.ToInt32(N));


            cmd.CommandText = sql;
            db.Close();

            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);

            DataTable dt = ds.Tables["TABLE"];

            foreach (DataRow row in dt.Rows)
            {
                msg = string.Format("{0}: {1}", row["MovieName"].ToString(), row["NumberOfReviews"].ToString());
                displayListBox.Items.Add(msg);

            }



        }// nMoviesNumReviews_Click()

        /**
         * Top N Users are displayed by number of reviews submitted
         */
        private void nUsersByReviews_Click(object sender, EventArgs e)
        {
            displayListBox.Items.Clear();

            if (this.textBox4.Text.Trim() == "")
            {
                MessageBox.Show("Cannot insert 'empty' number of Users");
                return;
            }

            db.Open();
            string msg, sql, N;
            object result;

            N = this.textBox4.Text;


            sql = string.Format("select count(UserID) from Reviews");
            cmd = new SqlCommand();
            cmd.Connection = db;
            cmd.CommandText = sql;

            result = cmd.ExecuteScalar();

            // handle if user enter N larger than available rows
            if (System.Convert.ToInt32(N) > System.Convert.ToInt32(result))
            {
                MessageBox.Show("Cant display more Movies than there are. Will display max number of movies.");
                N = result.ToString();
            }

            sql = string.Format(@"select top {0} Reviews.UserID, count(Reviews.Rating) as TotalReviews
                                    from Reviews
                                    group by Reviews.UserID
                                    order by count(Reviews.Rating) desc, Reviews.UserID asc;",
                                    System.Convert.ToInt32(N));


            cmd.CommandText = sql;
            db.Close();

            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            adapter.Fill(ds);

            DataTable dt = ds.Tables["TABLE"];

            foreach (DataRow row in dt.Rows)
            {
                msg = string.Format("{0}: {1}", row["UserID"].ToString(), row["TotalReviews"].ToString());
                displayListBox.Items.Add(msg);

            }
        }// nUsersByReviews_Click()



        
    }
}
