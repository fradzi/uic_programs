//
// CTA N-TIER APP
// Filip Radzikowski
// U. of Illinois, Chicago
// CS 480 Summer 2015
// Homework 6
//

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CTA_NTier
{
    public partial class Form1 : Form
    {
        // class-level field so all UI methods can access Business Tier:
        LBusinessTier.LBusinessAPI businessTier;

        public Form1()
        {
            InitializeComponent();


            // *******************************************************************************************
            //
            // Create instance of LBusinessTier.LBusinessAPI for app to call
            //
            businessTier = null;  // new ?
            // Initialize businessTier
            businessTier = new LBusinessTier.LBusinessAPI();

            //
            // *******************************************************************************************


        }

        private void Form1_Load(object sender, EventArgs e)
        {
            button1.Enabled = false;
            
            this.lstStations.Items.Add("");
            this.lstStations.Items.Add("[ Use File>>Load to display L stations... ]");
            this.lstStations.Items.Add("");

            this.lstStations.ClearSelected();

            toolStripStatusLabel1.Text = string.Format("Number of stations:  0");
        }


        //
        // File>>Exit:
        //
        private void exitToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            this.Close();
        }


        //
        // File>>Load Stations:
        //
        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            IReadOnlyList<LBusinessTier.LStation> stations;

            //
            // clear the UI of any current results:
            //
            ClearStationUI();

            //
            // now load the stations from the database:
            //
            try
            {
                //
                // call business tier to get stations:
                //
                stations = businessTier.GetLStations();

                //
                // now data-bind to list box for display:
                //
                // display event handling while we load:
                this.lstStations.SelectedIndexChanged -= new System.EventHandler(this.lstStations_SelectedIndexChanged);

                this.lstStations.DataSource = null;  // clear any existing data-binding:
                this.lstStations.Items.Clear();

                // data-bind, displaying station name with station ID behind:
                this.lstStations.DataSource = stations;
                this.lstStations.DisplayMember = "Name";
                this.lstStations.ValueMember = "ID";

                this.lstStations.ClearSelected();  // don't pre-select a station:

                // enable event handling now:
                this.lstStations.SelectedIndexChanged += new System.EventHandler(this.lstStations_SelectedIndexChanged);

                toolStripStatusLabel1.Text = string.Format("Number of stations:  {0:#,##0}", stations.Count());

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


        //
        // User has clicked on a station for more info:
        //
        private void lstStations_SelectedIndexChanged(object sender, EventArgs e)
        {
            // sometimes this event fires, but nothing is selected...
            if (this.lstStations.SelectedIndex < 0)   // so return now in this case:
                return;

            
            //
            // clear GUI in case this fails:
            //
            ClearStationUI();

            button1.Enabled = true;

            //
            // now display info about this station:
            //
            try
            {
                // 
                // what station did user click on?
                //
                string idstr = this.lstStations.SelectedValue.ToString();
                int id = Convert.ToInt32(idstr);

                //
                // ridership data:
                //
                int total = -1;
                double avgDaily = -1.0;



                // *******************************************************************************************
                //
                // Call business tier API to get Ridership total and average:
                //

                businessTier.Ridership(id, out total, out avgDaily);

                //
                // *******************************************************************************************



                this.txtTotalRidership.Text = total.ToString("#,##0");
                this.txtAvgDailyRidership.Text = string.Format("{0:#,##0}/day", avgDaily);

                //
                // stops at this station:
                //
                IReadOnlyList<LBusinessTier.LStop> stops;



                // *******************************************************************************************
                //
                // Call business tier API to get stops at this station:
                //

                stops = null; 

                stops = businessTier.GetLStops(id);

                foreach (var stop in stops)
                {
                    this.lstStops.Items.Add(stop.Name);

                }
                //
                // *******************************************************************************************



                // disable event handling while we setup data-binding:
                this.lstStops.SelectedIndexChanged -= new System.EventHandler(this.lstStops_SelectedIndexChanged);



                // *******************************************************************************************
                //
                // Data-bind the list of stops to the list box "lstStops".  Display "Name", but
                // the value behind the scenes should be the "ID".  Hint: see how stations are data-bound
                // above to the "lstStations" list box.
                //


                //
                // now data-bind to list box for display:
                //
                // display event handling while we load:
                this.lstStops.SelectedIndexChanged -= new System.EventHandler(this.lstStops_SelectedIndexChanged);

                this.lstStops.DataSource = null;  // clear any existing data-binding:
                this.lstStops.Items.Clear();

                // data-bind, displaying station name with station ID behind:
                this.lstStops.DataSource = stops;
                this.lstStops.DisplayMember = "Name";
                this.lstStops.ValueMember = "ID";

                this.lstStops.ClearSelected();  // don't pre-select a station:

                //
                // *******************************************************************************************



                this.lstStops.ClearSelected();  // don't pre-select a stop:

                // re-enable event handling:
                this.lstStops.SelectedIndexChanged += new System.EventHandler(this.lstStops_SelectedIndexChanged);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void ClearStationUI()
        {
            button1.Enabled = false;

            ClearStopUI();

            this.txtTotalRidership.Clear();
            this.txtTotalRidership.Refresh();

            this.txtAvgDailyRidership.Clear();
            this.txtAvgDailyRidership.Refresh();

            this.lstStops.DataSource = null;  // disable data-binding so we can clear:
            this.lstStops.Items.Clear();
            this.lstStops.Refresh();
        }


        //
        // user has clicked on a stop for more info:
        //
        private void lstStops_SelectedIndexChanged(object sender, EventArgs e)
        {
            // sometimes this event fires, but nothing is selected...
            if (this.lstStops.SelectedIndex < 0)   // so return now in this case:
                return;

            //
            // clear GUI in case this fails:
            //
            ClearStopUI();

            //
            // now display info about this stop:
            //
            try
            {
                // 
                // what stop did user click on?
                //
                string idstr = this.lstStops.SelectedValue.ToString();
                int id = Convert.ToInt32(idstr);


                // *******************************************************************************************
                //
                // TODO #5:  call the business tier api to get the details about this stop.
                // Display the returned data in the following UI controls:
                //
                // txtAccessible --- "yes" or "no"
                // txtDirection  --- direction of travel
                // txtLocation   --- (latitude, longitude)
                // lstLines      --- list box of line colors
                //

                LBusinessTier.LStopDetails stopDetails = businessTier.GetLStopDetails(id);

                var isAccessible = stopDetails.IsHandicapAccessible.ToString();
                if (isAccessible == "TRUE")
                {
                    this.txtAccessible.Text = "Yes";
                }
                else
                {
                    this.txtAccessible.Text = "No";
                }
                this.txtDirection.Text = stopDetails.Direction.ToString();
                this.txtLocation.Text = stopDetails.Latitude.ToString();

                foreach (var line in stopDetails.Lines)
                {
                    this.lstLines.Items.Add(line);
                }

                //
                // *******************************************************************************************

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void ClearStopUI()
        {
            this.txtAccessible.Clear();
            this.txtAccessible.Refresh();

            this.txtDirection.Clear();
            this.txtDirection.Refresh();

            this.txtLocation.Clear();
            this.txtLocation.Refresh();

            this.lstLines.Items.Clear();
            this.lstLines.Refresh();
        }

        private void SearchStations_Click(object sender, EventArgs e)
        {
            IReadOnlyList<LBusinessTier.LStation> stations;

            //
            // clear the UI of any current results:
            //
            ClearStationUI();

            //
            // now load the stations from the database:
            //
            try
            {
                // if textbox has no input
                if (string.IsNullOrWhiteSpace(FindStation_textBox1.Text))
                    return;

                string substring = this.FindStation_textBox1.Text.ToString();

                //
                // call business tier to get stations:
                //
                stations = businessTier.FindLStations(substring);

                //
                // now data-bind to list box for display:
                //
                // display event handling while we load:
                this.lstStations.SelectedIndexChanged -= new System.EventHandler(this.lstStations_SelectedIndexChanged);

                this.lstStations.DataSource = null;  // clear any existing data-binding:
                this.lstStations.Items.Clear();

                // data-bind, displaying station name with station ID behind:
                this.lstStations.DataSource = stations;
                this.lstStations.DisplayMember = "Name";
                this.lstStations.ValueMember = "ID";

                this.lstStations.ClearSelected();  // don't pre-select a station:

                // enable event handling now:
                this.lstStations.SelectedIndexChanged += new System.EventHandler(this.lstStations_SelectedIndexChanged);

                toolStripStatusLabel1.Text = string.Format("Number of stations:  {0:#,##0}", stations.Count());

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }


        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            try
            {
                // 
                // what station did user click on?
                //
                string idstr = this.lstStations.SelectedValue.ToString();
                int id = Convert.ToInt32(idstr);

                string fileName = businessTier.GetStationName(id);

                // Illegal corrector (from StackOverflow)
                string regexSearch =    new string(System.IO.Path.GetInvalidFileNameChars()) + 
                                        new string(System.IO.Path.GetInvalidPathChars());
                Regex rgx = new Regex(string.Format("[{0}]", Regex.Escape(regexSearch)));

                fileName = rgx.Replace(fileName, "");



                //
                // RidershipAnalyze for Weekdays
                //
                IReadOnlyList<LBusinessTier.LRidership> weekDay = businessTier.RidershipAnalyze(id, "W");

                if (weekDay == null)
                {
                    MessageBox.Show("There were no weekday riderships.");
                }
                else
                {
                    using (System.IO.StreamWriter writer = new System.IO.StreamWriter(fileName + "WeekdayRidership.csv"))
                    {
                        writer.WriteLine("Date, Rides");
                        foreach (var line in weekDay)
                        {
                            writer.WriteLine(line.Date.ToString() + ", " + line.Rides.ToString());
                        }
                    }    
                }


                //
                // RidershipAnalyze for Saturdays
                //
                IReadOnlyList<LBusinessTier.LRidership> saturday = businessTier.RidershipAnalyze(id, "A");

                if (saturday == null)
                {
                    MessageBox.Show("There were no Saturday riderships.");
                }
                else
                {
                    using (System.IO.StreamWriter writer = new System.IO.StreamWriter(fileName + "SaturdayRidership.csv"))
                    {
                        writer.WriteLine("Date, Rides");
                        foreach (var line in saturday)
                        {
                            writer.WriteLine(line.Date.ToString() + ", " + line.Rides.ToString());
                        }
                    }
                }


                //
                // RidershipAnalyze for Sunday and Holidays
                //
                IReadOnlyList<LBusinessTier.LRidership> sunday = businessTier.RidershipAnalyze(id, "U");

                if (sunday == null)
                {
                    MessageBox.Show("There were no Sunday riderships.");
                }
                else
                {
                    using (System.IO.StreamWriter writer = new System.IO.StreamWriter(fileName + "SundayHolidayRidership.csv"))
                    {
                        writer.WriteLine("Date, Rides");
                        foreach (var line in sunday)
                        {
                            writer.WriteLine(line.Date.ToString() + ", " + line.Rides.ToString());
                        }
                    }
                }


                MessageBox.Show("Ridership Data Analyzed and sent to .CSV files.");

            }
            catch (Exception ex)
            {
                MessageBox.Show("Error LBusinessTier.LRidership Output to .csv");
                throw;
            }


        }

    }//class
}//namespace
