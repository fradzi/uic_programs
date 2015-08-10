//
// uiTunes Music Purchase Application
//
// Filip Radzikowski
// U. of Illinois, Chicago
// CS480, Summer 2015
// Homework 3
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

namespace uiTunesPurchaseApp
{
    public partial class PurchaseApp : Form
    {
        
        //
        // Fields
        //
        bool firstNameClick = true;
        bool lastNameClick = true;
        bool passwordClick = true;
        string connectionInfo;

        // 
        // constructor: setup connection info
        //
        public PurchaseApp()
        {
            InitializeComponent();

            string filename = "uiTunes.mdf";
            connectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", filename);
       
        }

        private void PurchaseApp_Load(object sender, EventArgs e)
        {
            // Set to Albums Initially
            this.PurchaseType.SelectedIndex = 0;

            //this.Purchase_Button.Enabled = false;

        }

        //
        // User chooses Songs or Albums from ComboBox to view list from listView
        //
        private void PurchaseType_SelectedIndexChanged(object sender, EventArgs e)
        {
            
            this.listBox1.Items.Clear();

            string nameType;

            SqlConnection db = new SqlConnection(connectionInfo);
            DataSet ds;
            
            db.Open();
            
            
            // If Albums Selected
            if (this.PurchaseType.SelectedIndex.Equals(0))
            {

                string sql = String.Format(@"Select AlbumName from Albums;");
                
                SqlCommand cmd = new SqlCommand();
                SqlDataAdapter adapter = new SqlDataAdapter(cmd);
                ds = new DataSet();

                cmd.Connection = db;
                cmd.CommandText = sql;

                adapter.Fill(ds);

                // For Printing in Listbox
                nameType = "AlbumName";
            }

            // If Songs Selected   
            else {

                string sql = String.Format(@"Select SongName from Songs;");

                SqlCommand cmd = new SqlCommand();
                SqlDataAdapter adapter = new SqlDataAdapter(cmd);
                ds = new DataSet();
                
                cmd.Connection = db;
                cmd.CommandText = sql;

                adapter.Fill(ds);

                //For Printing in Listbox
                nameType = "SongName";
            
            }

            db.Close();

            DataTable dt = ds.Tables["TABLE"];

            foreach (DataRow row in dt.Rows)
            {       
                string msg = String.Format("{0}", row[nameType]);
                listBox1.Items.Add(msg);
            }
        }

        //
        // User chooses Song or Album to view Detials 
        //
        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            listView1.Items.Clear();
            
            SqlConnection db = new SqlConnection(connectionInfo);

            object result;
            string msg;
            string selectedItemName;
            string selectedItemType;
            
            // Whether user is looking at Albums or Songs
            if (this.PurchaseType.SelectedIndex.Equals(0))
            {
                selectedItemType = "Album";
            }
            else
            {
                selectedItemType = "Song";
            }

            //
            // 1. Get Selected Album or Song Name
            //
            selectedItemName = this.listBox1.SelectedItem.ToString();

     

            db.Open();

            SqlCommand cmd = new SqlCommand();
            cmd.Connection = db;

            //
            // 2. Get ItemID From ItemName
            //
            string sql = String.Format(@"Select {0}ID from {0}s
                                        Where {0}Name = '{1}';",
                                        selectedItemType, selectedItemName);

            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            int selectedItemID = Convert.ToInt32(result);

                                                                                  

            //
            // 3. Get Artists involved with Item
            //
            sql = String.Format(@"
                                        Select ArtistName from Artists
                                        INNER JOIN
	                                        (
		                                        Select ArtistID from {0}Details
		                                        where {0}ID = {1}
	                                        ) T
                                        ON Artists.ArtistID = T.ArtistID;
                                        ", selectedItemType, selectedItemID);


            cmd.CommandText = sql;

            SqlDataAdapter adapter = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();

            adapter.Fill(ds);

            this.listView1.Items.Add("Artist(s) :");
            DataTable dt = ds.Tables["Table"];
            foreach (DataRow row in dt.Rows)
            {
                this.listView1.Items.Add("    " + row["ArtistName"].ToString());
            }

            //result = cmd.ExecuteScalar();
            //string selectedItemArtist = Convert.ToString(result);

            //msg = String.Format("Artist(s) : \t{0}", selectedItemArtist);
            //this.listView1.Items.Add(msg);
   

            //
            // 4. Get Item release date
            //
            sql = String.Format(@"Select YearRel from {0}s
                                    Where {0}ID = {1}", selectedItemType, selectedItemID);
            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();
            
            string selectedItemYearRel;            
            
            if (result.ToString() == string.Empty) // Because row existed but value was emtpy, otherwise use null
                {selectedItemYearRel = "N/A"; }
            else
                selectedItemYearRel = Convert.ToString(result);

            msg = String.Format("Release Year : \t{0}", selectedItemYearRel);
            this.listView1.Items.Add(msg);
            
            //
            // 5. Get Price of Item
            //
            sql = String.Format(@"Select Price from {0}s
                                    Where {0}ID = {1}", selectedItemType, selectedItemID);

            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();
            double selectedItemPrice;
            
            //If there is no price
            if (result == null || result.ToString() == string.Empty)
                selectedItemPrice = 0.00;
            else
                selectedItemPrice = Convert.ToDouble(result);
 
            msg = String.Format("Price : \t{0}", selectedItemPrice.ToString("c2")); // formating into Money
            this.listView1.Items.Add(msg);

            //
            // 6. Get Total number of reviews
            //
            sql = String.Format(@"
                                
                                Declare @T As Integer
                                Select @T=ReviewItemTypeID from ReviewItemTypes
                                Where ReviewItemTypeName = '{0}'

                                Select Count(*) From Reviews
                                Where ReviewItemTypeID = @T and ReviewItemID = {1};
                                ", selectedItemType, selectedItemID);

            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();
            string selectedItemNumReviews;
            
            // If there are no reviews
            if (result == null || result.ToString() == string.Empty)
                selectedItemNumReviews = "0";
            else   
                selectedItemNumReviews = Convert.ToString(result);

            msg = String.Format("Total Reviews : \t{0}", selectedItemNumReviews);
            this.listView1.Items.Add(msg);
            

            //
            // 7. Get Average Review
            //
            sql = String.Format(@"
                                
                                Declare @T As Integer
                                Select @T=ReviewItemTypeID from ReviewItemTypes
                                Where ReviewItemTypeName = '{0}'

                                Select Round(AVG(Cast(Rating as float)),4) From Reviews
                                Where ReviewItemTypeID = @T and ReviewItemID = {1};  
                                ", selectedItemType, selectedItemID);
            
            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();
            string selectedItemAvgReviews;
            
            // If there is no Average 
            if (result == null || result.ToString() == string.Empty )
                selectedItemAvgReviews = "N/A";
            else
                selectedItemAvgReviews = Convert.ToString(result);

            msg = String.Format("Average Review : \t{0}", selectedItemAvgReviews);
            this.listView1.Items.Add(msg);
            
            


            db.Close();

        }

        //
        // Checks User Credentials and gives access to purchases
        //
        private void GoToAccount_Button_Click(object sender, EventArgs e)
        {
            SqlConnection db = new SqlConnection(connectionInfo);

            string firstName = this.FirstName_textBox1.Text;
            string lastName = this.LastName_textBox2.Text;
            string password = this.Password_textBox3.Text;
            string msg, sql;
            object result;

            // For SQL Queries
            firstName = firstName.Replace("'", "''");
            lastName = lastName.Replace("'", "''");

            db.Open();

            SqlCommand cmd = new SqlCommand();
            cmd.Connection = db;

            //
            // 1. Check if valid User
            //
            sql = String.Format(@"
                                Select UserID from Users	
                                Where FirstName = '{0}' and LastName = '{1}' 
                                AND Pwd = '{2}'   
                                ", firstName, lastName, password);
            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            if (result == null)
            {
                // Notify User Incorrect Info 
                MessageBox.Show("Oops...who are you? Lets try again...");
                // Reset all Entry Prompts, SecurityChar, 
                this.LogOut_button.PerformClick();
                return;
            }



            //
            // 2. Check for Users account balance
            sql = String.Format(@"
        
                                        Declare @acctBal as Money
                                        Select @acctBal = AcctBal from Users	
                                        Where FirstName = '{0}' and LastName = '{1}' and Pwd = '{2}'

                                        if @acctBal = '' 
	                                        set @acctBal = null
                                        select @acctBal
                                        ", firstName, lastName, password);


            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            db.Close();

            double bal = 0.00;
            string balance = string.Empty;

            if (result == DBNull.Value)
            {
                bal = 0.00;
                balance = bal.ToString("c2");
                msg = String.Format("Welcome {0}! You have {1} to (not) spend! Stay Optimistic!!", firstName, balance);
            }
            else if ((bal = System.Convert.ToDouble(result.ToString())) < 0.00)
            {
                
                balance = bal.ToString("N2");
                msg = String.Format("Welcome {0}! You have $ {1}...Ouch!!", firstName, balance);
            }
            else
            {
                balance = bal.ToString("c2");
                msg = String.Format("Welcome {0}! You have {1} to spend! Get to it!!", firstName, balance);
            }
            MessageBox.Show(msg);

            this.Balance_listView2.Items.Add(balance);
            this.Purchase_Button.Enabled = true;
            

        }
        
        private void Purchase_button2_Click(object sender, EventArgs e)
        {

            //check if purchased
            //check if user has enough to buy


            SqlConnection db = new SqlConnection(connectionInfo);
            string sql, firstName, lastName, itemName, itemType;
            object result;

            itemType = this.PurchaseType.Text.ToString();
            itemName = this.listBox1.SelectedItem.ToString();
            firstName = this.FirstName_textBox1.Text.ToString();
            lastName = this.LastName_textBox2.Text.ToString();
            // For SQL Queries
            firstName = firstName.Replace("'", "''");
            lastName = lastName.Replace("'", "''");
            itemName = itemName.Replace("'", "''");

            
            db.Open();

            SqlCommand cmd = new SqlCommand();
            cmd.Connection = db;

            if(itemType == "Songs")
                itemType = "Song";
            else itemType = "Album";





            //
            // 1. Check if User already owns Item
            //
            sql = String.Format(@"
                        Declare @TypeID as Integer
                        Select @TypeID = PurchaseItemTypeID from PurchaseItemTypes
                        Where PurchaseItemTypeName = '{0}'

                        Declare @ItemID as Integer
                        Select @ItemID = {0}ID from {0}s
                        Where {0}Name = '{1}'

                        Select count(*) from PurchaseDetails
                        INNER JOIN
	                        (
		                        select PurchaseID from Purchases 
		                        INNER JOIN
			                        (		
				                        select UserID from Users
				                        Where FirstName = '{2}' and LastName = '{3}'
			                        ) T1
		                        ON Purchases.UserID = T1.UserID
	                        ) T2
                        ON PurchaseDetails.PurchaseID = T2.PurchaseID
                        WHERE PurchaseDetails.PurchaseItemTypeID = @TypeID 
                        AND PurchaseDetails.PurchaseItemID = @ItemID;      
                        ", itemType, itemName,
                         firstName, lastName);


            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            //If User already has the Item then inform and return
            bool hasItem = Convert.ToBoolean(result);
            if (hasItem)
            {
                MessageBox.Show("Looks like you already got " + itemName + ".. Go get you something else..");
                return;
            }
   
            //
            // 2. Check if User has enough doe
            //

            sql = String.Format(@"  Declare @acct as smallMoney
                                    Declare @cost as smallMoney
                                    Declare @result as Integer

                                    Select @acct = AcctBal From Users 
                                    Where FirstName = '{0}' and LastName = '{1}';

                                    Select @cost = Price from {2}s 
                                    Where {2}Name = '{3}'

                                    if @acct < @cost
                                    begin set @result = 0 end

                                    else begin set @result = 1 end;

                                    select @result;"
                                    , firstName, lastName, itemType, itemName);

            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();
            
            bool hasBalance = Convert.ToBoolean(result);

            if (!hasBalance)
            {
                MessageBox.Show("Sorry not enough doe..go get some and come back.."+
                                "we'll wait");
                return;
            }


            sql = String.Format(@"
                                    Declare @userID as Integer;
                                    Declare @bal as smallMoney;
                                    Declare @cost as smallMoney;
                                    Declare @diff as smallMoney;

                                    Declare @PurchaseItemTypeID	 as TinyInt;
                                    Declare @PurchaseItemID as Integer;

                                    Select @PurchaseItemTypeID=PurchaseItemTypeID from PurchaseItemTypes
                                    Where PurchaseItemTypeName = '{0}';

                                    Select @PurchaseItemID={0}ID from {0}s
                                    Where {0}Name = '{1}'; 

                                    Select @userID=UserID from Users
                                    Where FirstName = '{2}' and LastName = '{3}';

                                    Select @bal=AcctBal From Users
                                    Where UserID = @userID;

                                    Select @cost=Price from {0}s
                                    Where {0}Name = '{1}';

                                    Set @diff = @bal - @cost

                                    select @diff

                                    Insert into Purchases (UserID,AmountPaid, PurchaseDate )
                                    Values(@userID, @cost, GetDate());

                                    Insert into PurchaseDetails (PurchaseID, PurchaseItemTypeID, PurchaseItemID)
                                    Values(@@IDENTITY, @PurchaseItemTypeID, @PurchaseItemID);

                                    UPDATE Users 
                                    Set AcctBal = @diff Where UserID = @userID;
                                    Select @diff;"
                                    
                                    , itemType, itemName, firstName, lastName);


            cmd.CommandText = sql;
            result = cmd.ExecuteScalar();

            if (result == null)
                MessageBox.Show("There was an issue with Uploading.");
            else
            {
                
                this.Balance_listView2.Clear();
                double balance = Convert.ToDouble(result);
                this.Balance_listView2.Items.Add(balance.ToString("c2"));
                MessageBox.Show("Success!! Enjoy your tunes!!");
            }





            
            db.Close();

        }

        private void FirstName_textBox1_Click(object sender, EventArgs e)
        {
            if (firstNameClick)
            {
                this.FirstName_textBox1.Clear();
                firstNameClick = false;
            } 
        }

        private void LastName_textBox2_Click(object sender, EventArgs e)
        {
            if (lastNameClick)
            {
                this.LastName_textBox2.Clear();
                lastNameClick = false;
            } 
        }
        // Keep Security Char On for case where user Clicks into Password Textbox
        private void Password_textBox3_Click(object sender, EventArgs e)
        {
            if (passwordClick)
            {
                this.Password_textBox3.Clear();
                passwordClick = false;
                this.Password_textBox3.UseSystemPasswordChar = true; // Turn Security Char On
            } 
        }

        private void LogOut_button_Click(object sender, EventArgs e)
        {
            firstNameClick = true;
            lastNameClick = true;
            passwordClick = true;

            this.FirstName_textBox1.Text = "Enter FIRST Name";
            this.LastName_textBox2.Text = "Enter Last Name";
            this.Password_textBox3.Text = "Enter Password";
            this.Password_textBox3.UseSystemPasswordChar = false;

            this.Balance_listView2.Clear();

            this.Purchase_Button.Enabled = false;

        }

        // Keep Security Char On for case where User Tabs into Password Textbox
        private void Password_textBox3_Enter(object sender, EventArgs e)
        {
            if (passwordClick)
            {
                this.Password_textBox3.Clear();
                passwordClick = false;
                this.Password_textBox3.UseSystemPasswordChar = true; // Turn Security Char On
            } 
        }


        

        //enable button
        // button1.Enabled = true;

        //scope_identity // give last primary key id 
        // convert(date, getDate())) // to get date
        // use system password char
        
        // sql server
    }
}
