//
// F# program to analyze rainfall data
// Filip Radzikowski
// U. of Illinois, Chicago
// CS 341, Spring 2015
// Homwork 5
//



#light

//
// ReadFile: reads a file line by line, returning a list
// of strings, one per line.
//
let ReadFile filename = 
  [ for line in System.IO.File.ReadLines(filename) -> line ]


//
// ParseLine: given a line from the rainfall file, parses this
// string into a tuple (year, values) where values is a list of
// the 12 rainfall data values for year.
//
let ParseLine (line:string) = 
  let strings = line.Split('\t')
  let strlist = Array.toList(strings)
  let year    = System.Int32.Parse(strlist.Head)
  let values  = List.map System.Double.Parse strlist.Tail
  (year, values)


//
// Given a tuple (year, values), prints these to the console
//
let PrintYearData (year:int, values:double list) = 
  printfn ""
  printfn "%A: %A" year values

//
// print out the average rainfall for the year
//
let printAvg (yr: int, avg: double) =
  printfn "%A: %A" yr avg

//
// function for getting the average rainfall for the year
//
let average data = 
    let avrg = List.map (fun (yr:int, va:double list)-> yr, List.average va) data
    List.iter (fun (yr:int, avg: double)-> printAvg(yr, avg)) avrg
 
//
// fucntion to get max rain fall from database
//
let maxRainFall data =
  let maxMonth = List.map(fun (yr:int, va:double list)-> List.max va) data
  let max = List.max maxMonth       
  printfn "Maximum Rainfall: %A" max

//
// function to get min rain fall from database
//
let minRainFall data =
  let minMonth = List.map(fun (yr:int, va:double list)-> List.min va) data
  let min = List.min minMonth 
  printfn "Minimum Rainfall: %A" min
        
 
//
//Get the value of each column at a specific index and store this 
//data into a list called average. This fuction gets called for every
//month.
//
let computeEachMonth index data = 
  let currMonth = List.map(fun (yr:int, va:double list) -> List.nth va index) data
  let avg = List.average currMonth
  avg

//
//This function prints out the monthly averages through
//out all the years.
//
let rec printMonthAvg (index:int, list:double list) = 
  if list = [] then
    printfn "" 
  else
    let months = [ "Jan"; "Feb"; "Mar"; "Apr"; "May"; "Jun"; "Jul"; "Aug"; "Sep"; "Oct"; "Nov"; "Dec" ]
    let monthName = List.nth months index
    printfn "%s: %A " monthName list.Head
    let i = index + 1
    printMonthAvg (i, list.Tail)



//
// Main:
//
[<EntryPoint>]
let main argv = 
  // read entire file as list of strings:
  let file = ReadFile "rainfall-midway.txt"
  let rainfallData = List.map(fun x ->  ParseLine x) file
  
  //call average fucntion to calculate the yearly average
  average rainfallData 
  printfn ""

  // create a list of 12 values to be used as the
  // indecies for computeEachMonth function call
  let monthsArray = [0..11]
  
  // creating a list of monthly averages using an index
  let listOfMonthlyAvg = List.map(fun (index:int) -> computeEachMonth index rainfallData) monthsArray
  printMonthAvg (0, listOfMonthlyAvg) 
  
  // call min and max rain fall fucntions
  maxRainFall rainfallData
  minRainFall rainfallData


  // debugging: print what file list looks like:
  //printfn ""
  //printfn "%A" file
  //printfn ""

  // let's parse first line into tuple (year, list of rainfall values),
  // and then print for debugging:
  let (year, values) = ParseLine file.Head
  //PrintYearData (year, values)

  // done:
  printfn ""
  printfn ""
  0 // return 0 => success
