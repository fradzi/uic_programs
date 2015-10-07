//
// Data Access Tier:  interface between business tier and data store.
//

using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;


namespace DataAccessTier
{

  public class Data
  {
    //
    // Fields:
    //
    private string _DBFile;
    private string _DBConnectionInfo;

    //
    // constructor:
    //
    public Data(string DatabaseFilename)
    {
      _DBFile = DatabaseFilename;
      _DBConnectionInfo = String.Format(@"Data Source=(LocalDB)\v11.0;AttachDbFilename=|DataDirectory|\{0};Integrated Security=True;", DatabaseFilename);
    }

    //
    // TestConnection:  returns true if the database can be successfully opened and closed,
    // false if not.
    //
    public bool TestConnection()
    {
      SqlConnection db = new SqlConnection(_DBConnectionInfo);

      bool  state = false;

      try
      {
        db.Open();

        state = (db.State == ConnectionState.Open);
      }
      catch
      {
        // nothing, just discard:
      }
      finally
      {
        db.Close();
      }

      return state;
    }

    //
    // ExecuteScalarQuery:  executes a scalar Select query, returning the single result 
    // as an object.  
    //
    public object ExecuteScalarQuery(string sql)
    {

        SqlConnection db = new SqlConnection(_DBConnectionInfo);
        SqlCommand cmd = new SqlCommand();

        db.Open();
        cmd.Connection = db;
        cmd.CommandText = sql;
        object result = cmd.ExecuteScalar();
        db.Close();

        if (result == null)
        {
            
            return null;
        }
        else
        {
            return result;
        }
      
    }

    // 
    // ExecuteNonScalarQuery:  executes a Select query that generates a temporary table,
    // returning this table in the form of a Dataset.
    //
    public DataSet ExecuteNonScalarQuery(string sql)
    {
        SqlConnection db = new SqlConnection(_DBConnectionInfo);
          SqlCommand cmd = new SqlCommand();
          cmd.Connection = db;
          cmd.CommandText = sql;

          db.Open();
          SqlDataAdapter adapter = new SqlDataAdapter(cmd);
          DataSet ds = new DataSet();
          adapter.Fill(ds);
          db.Close();

          if (ds == null)
            return null;
          else 
            return ds;
    
        //SqlConnection db = new SqlConnection(_DBConnectionInfo);
        //SqlCommand cmd = new SqlCommand();

        //db.Open();
        //SqlDataAdapter adapter = new SqlDataAdapter(cmd);
        //DataSet ds = new DataSet();
        //adapter.Fill(ds);
        //db.Close();

        //if (ds == null)
        //{
        //    return null;
        //}
        //else
        //{
        //    return ds;
        //}
        
    }

    //
    // ExecutionActionQuery:  executes an Insert, Update or Delete query, and returns
    // the number of records modified.
    //
    public int ExecuteActionQuery(string sql)
    {
        SqlConnection db = new SqlConnection(_DBConnectionInfo);
        SqlCommand cmd = new SqlCommand();
        
        cmd.Connection = db;
        cmd.CommandText = sql;
        
        db.Open();
        int result = cmd.ExecuteNonQuery();
        db.Close();

        if (result == null)
        {
            return -1;
        }
        else
        {
            return result; 
        }
        
    }

  }//class

}//namespace
