using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LBusinessTier
{

    public class LStation
    {
        public int ID { get; private set; }
        public string Name { get; private set; }

        public LStation(int stationID, string stationName)
        {
            ID = stationID;
            Name = stationName;
        }

    }

    public class LStop
    {
        public int ID { get; private set; }

        public string Name { get; private set; }

        public LStop(int stopID, string stopName)
        {
            ID = stopID;
            Name = stopName;
        }
    }

    public class LStopDetails
    {
        public bool IsHandicapAccessible { get; private set; }

        public IReadOnlyList<string> Lines { get; private set; }

        public string Direction { get; private set; }
        public double Latitude { get; private set; }
        public double Longitude { get; private set; }

        public LStopDetails(bool stopIsHandicapAccessible, IReadOnlyList<string> stopLines, string stopDirection, double stopLatitude, double stopLongitude)
        {
            IsHandicapAccessible = stopIsHandicapAccessible;
            Lines = stopLines;
            Direction = stopDirection;
            Latitude = stopLatitude;
            Longitude = stopLongitude;
        }
    }

    public class LRidership
    {
        public string Date { get; private set; }
        public int Rides { get; private set; }

        public LRidership(string date, int rides)
        {
            Date = date;
            Rides = rides;
        }
    }



}//namespace
