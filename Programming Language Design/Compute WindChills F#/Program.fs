//
//  F# program to compute windchills.
//  Filip Radzikowski
//  U. Illinois, Chicago
//  CS341, Spring 2015
//  Homework 4
//

#light

let windchill T W =
  //let T = 10.00
  let w = System.Math.Pow(W, 0.16)        // Wind
  let WC = 35.7 + 0.6*T - 35.7*w + 0.43*T*w 
  WC

[<EntryPoint>]
let main argv = 
  printf "Please enter temperature (degrees F): "

  let input = System.Console.ReadLine()
  let T = System.Convert.ToDouble(input)
  
  let WS = [1.0..20.0]
  let windchills = List.map (fun W->windchill T W) WS
  
  printfn "%A" windchills
  printfn ""
  0 // return an integer exit 



  
