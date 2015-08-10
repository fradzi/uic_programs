using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LBusinessTier
{

    public class LBusinessAPI
    {

        //
        // GetLStations:
        //
        public IReadOnlyList<LStation> GetLStations()
        {
            List<LStation> stations = new List<LStation>();

            try
            {
                // gain access to the data tier:
                LDataAccessTier.CTADataContext cta = new LDataAccessTier.CTADataContext();
                
                // retrieve all the Station entities from the database:
                var query = from station in cta.Stations
                            orderby station.Name
                            select station;

                // now create business objects from the Station entities, and build a list
                // to return:
                foreach (var station in query)
                {
                    LStation s = new LStation(station.StationID, station.Name);
                    stations.Add(s);
                }
            }
            catch (Exception ex)
            {
                string msg = string.Format("Error in LBusinessAPI.GetLStations: '{0}'", ex.Message);
                throw new ApplicationException(msg);
            }

            return stations;
        }


        //
        // GetLStops:
        //
        public IReadOnlyList<LStop> GetLStops(int stationID)
        {
            List<LStop> stops = new List<LStop>();

            try
            {
                // gain access to the data tier:
                LDataAccessTier.CTADataContext cta = new LDataAccessTier.CTADataContext();

                // 
                // various ways to do this, but LINQ to SQL understands relationships between
                // tables based on primary and foreign keys, so we can lookup station, and then
                // ask for associated stops:
                //

                // so first we lookup the station:
                var query = from station in cta.Stations
                            where station.StationID == stationID
                            select station;

                // make sure we found it:
                if (query.Count() == 0)
                    throw new ApplicationException("unknown station ID");

                // we found a station, retrieve it:
                LDataAccessTier.Station Lstation = query.First();

                // now get the Stop entities from the Station entity:
                var query2 = from stop in Lstation.Stops
                             orderby stop.Name
                             select stop;

                // finally, create business objects from the Stop entities, and build a list
                // to return:
                foreach (var stop in query2)
                {
                    LStop s = new LStop(stop.StopID, stop.Name);
                    stops.Add(s);
                }

            }
            catch (Exception ex)
            {
                string msg = string.Format("Error in LBusinessAPI.GetLStops: '{0}'", ex.Message);
                throw new ApplicationException(msg);
            }

            return stops;
        }


        //
        // GetLStopDetails:
        //
        public LStopDetails GetLStopDetails(int stopID)
        {
            LStopDetails details = null;

            try
            {
                // gain access to the data tier:
                LDataAccessTier.CTADataContext cta = new LDataAccessTier.CTADataContext();

                // first we lookup the stop:
                var query = from stop in cta.Stops
                            where stop.StopID == stopID
                            select stop;

                // make sure we found it:
                if (query.Count() == 0)
                    throw new ApplicationException("unknown stop ID");

                // we found one, so get the Stop entity:
                LDataAccessTier.Stop Lstop = query.First();

                // the Stop entity contains most of the info --- direction, lat, long, etc. --- but
                // we need to get the colors of the lines for this stop:
                List<string> lines = new List<string>();

                var query2 = from stopdetails in Lstop.StopDetails
                             select stopdetails.Line.Color;

                foreach (string color in query2)
                    lines.Add(color);

                // finally, create the business object to hold these details and return to UI:
                details = new LStopDetails(Lstop.ADA, lines, Lstop.Direction, Lstop.Latitude, Lstop.Longitude);
            }
            catch (Exception ex)
            {
                string msg = string.Format("Error in LBusinessAPI.GetLStopDetails: '{0}'", ex.Message);
                throw new ApplicationException(msg);
            }

            return details;
        }


        //
        // Ridership:
        //
        public void Ridership(int stationID, out int total, out double avgDaily)
        {
            try
            {
                // gain access to the data tier:
                LDataAccessTier.CTADataContext cta = new LDataAccessTier.CTADataContext();

                // retrieve all the daily totals for this station:
                var query = from ridership in cta.Riderships
                            where ridership.StationID == stationID
                            select ridership.DailyTotal;

                if (query.Count() == 0)  // no data for this station?
                {
                    total = 0;
                    avgDaily = 0.0;

                    return;
                }

                // otherwise compute total and average of the riderships:
                total = query.Sum();
                avgDaily = query.Average();
            }
            catch (Exception ex)
            {
                total = 0;
                avgDaily = 0.0;

                string msg = string.Format("Error in LBusinessAPI.Ridership: '{0}'", ex.Message);
                throw new ApplicationException(msg);
            }
        }


        //
        // FindStations:
        //
        public IReadOnlyList<LStation> FindLStations(string substring)
        {
            List<LStation> stations = new List<LStation>();

            try
            {
                // gain access to the data tier:
                LDataAccessTier.CTADataContext cta = new LDataAccessTier.CTADataContext();

                // retrieve all the Station entities from the database:
                var query = from station in cta.Stations
                            where station.Name.Contains(substring)
                            orderby station.Name
                            select station;

                // now create business objects from the Station entities, and build a list
                // to return:
                foreach (var station in query)
                {
                    LStation s = new LStation(station.StationID, station.Name);
                    stations.Add(s);
                }
            }
            catch (Exception ex)
            {
                string msg = string.Format("Error in LBusinessAPI.GetLStations: '{0}'", ex.Message);
                throw new ApplicationException(msg);
            }

            return stations;
        }

        //
        // Creating a Lists of Lridership to Send back to UI
        //
        public IReadOnlyList<LRidership> RidershipAnalyze(int id, string dayType)
        {
            List<LRidership> ridershipData = new List<LRidership>();

 
            try
            {
                // gain access to the data tier:
                LDataAccessTier.CTADataContext cta = new LDataAccessTier.CTADataContext();

                // retrieve all the Ridership entities from the database:
                var query = from Ridership in cta.Riderships
                            where Ridership.TypeOfDay.Equals(dayType) && Ridership.StationID.Equals(id)
                            orderby Ridership.TheDate
                            select Ridership;

                // check that query returned with a value
                if (query.Count() == 0)
                {
                    return null;
                }

                // now create business objects from the Ridership entities, and build a list
                // to return:
                foreach (var ridership in query)
                {
                    LRidership s = new LRidership(ridership.TheDate.Date.ToString("M/d/yyyy"),
                                                  Convert.ToInt32(ridership.DailyTotal.ToString()));
                    ridershipData.Add(s);
                }
            }
            catch (Exception ex)
            {
                string msg = string.Format("Error in LBusinessAPI.LRidership: '{0}'", ex.Message);
                throw new ApplicationException(msg);
            }

            return ridershipData;

        }


        //
        // Convert StationID to StationName
        //
        public string GetStationName(int id)
        {
            
            string StationName = string.Empty;
            
            try
            {
                // gain access to the data tier:
                LDataAccessTier.CTADataContext cta = new LDataAccessTier.CTADataContext();

                // retrieve all the Ridership entities from the database:
                var query = from Station in cta.Stations
                            where Station.StationID == id
                            select Station.Name;

                // check that query returned with a value
                if (query == null)
                {
                    return StationName;
                }
                // Grab the first ( and only) query result
                else
                {
                    StationName = query.First().ToString();
                }
           
                
            }
            catch (Exception ex)
            {
                string msg = string.Format("Error GetStationName : '{0}'", ex.Message);
                throw new ApplicationException(msg);
            }

            return StationName;

        }



    }//class
}//namespace
