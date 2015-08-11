//
// F#-based PPM image library.
// Filip Radzikowski
// U. of Illinois, Chicago
// CS 341, Spring 2015
// Homwork 6
//

module PPMImageLibrary

#light


//
// DebugOutput:
//
// Outputs to console, which appears in the "Output" window pane of
// Visual Studio when you run with debugging (F5).
//
let rec private OutputImage(image:int list list) = 
  if image = [] then
    printfn "**END**"
  else
    printfn "%A" image.Head
    OutputImage(image.Tail)
           
let DebugOutput(width:int, height:int, depth:int, image:int list list) =
  printfn "**HEADER**"
  printfn "W=%A, H=%A, D=%A" width height depth
  printfn "**IMAGE**"
  OutputImage(image)

//
// TransformFirstRowWhite:
//
// An example transformation: replaces the first row of the given image
// with a row of all white pixels.
//
let rec BuildRowOfWhite cols white = 
  if cols = 0 then
    []
  else 
    // 1 pixel, i.e. RGB value, followed by remaining pixels:
    white :: white :: white :: BuildRowOfWhite (cols-1) white

let TransformFirstRowWhite(width:int, height:int, depth:int, image:int list list) = 
  // first row all white :: followed by rest of original image
  BuildRowOfWhite width depth :: image.Tail


//
// WriteP3Image:
//
// Writes the given image out to a text file, in "P3" format.  Returns true if successful,
// false if not.
//
let rec WriteP3Image(filepath:string, width:int, height:int, depth:int, image:int list list) = 

  //Convert width and height to string and concatinate
  let w = width.ToString()
  let h = height.ToString()
  let wh = String.concat " " [w;h]
  //Convert depth to string
  let d = depth.ToString()

  // Convert a list to a string recursively
  let rec convertToString list = 
    match list with
    | head::tail->head.ToString() + " " + convertToString tail
    | []->""

  // This function takes a list of lists and passes each individual list to converToString()
  let listOfStrings (L:int list list) =  List.map(fun x-> convertToString x ) L
  
  // create a list of strings
  let list1 = listOfStrings image
  // create a single string
  let list2 = convertToString list1

  let L = ["P3"; wh; d; list2]
  System.IO.File.WriteAllLines(filepath, L)
  
  true  // success


//
// Takes rgb values and produces an average value for each rgb grouping
//
let rec getAvgs (data: int list) = 
  if data = [] then
    []
  else 
    ((data.Head + data.Tail.Head + data.Tail.Tail.Head)/3) :: getAvgs (data.Tail.Tail.Tail)

//
// Takes the averages produced in getAvgs and applies the value to rgb
//
let rec toThree (x: int list) =
  if x = [] then
    []
  else 
    x.Head :: x.Head :: x.Head :: toThree x.Tail


//-------------------------------------------------------------------------------------TransformGrayscale---//
// Produces the grayscale using the toThree recursive function and getAvgs function
let TransformGrayscale(width:int, height:int, depth:int, image:int list list) = 
  
  let avgList = List.map(fun x-> getAvgs x) image
  let transImage = List.map(fun x-> toThree x) avgList 
  
  transImage  
  
//
// Applies arithmetic to rgb
//
let rec getInvert (data: int list) = 
  if data = [] then
    []
  else
    (255 - data.Head)::(255 - data.Tail.Head)::(255 - data.Tail.Tail.Head) :: getInvert (data.Tail.Tail.Tail)

//----------------------------------------------------------------------------------------TransformInvert---//
// inverts the colors on the picture into a color negative 
// using get recursive fucntion getInvert
let TransformInvert(width:int, height:int, depth:int, image:int list list) = 
  
  let invertImage = List.map(fun x-> getInvert x) image
  
  invertImage

//
// reverses each rgb value to bgr so when entire int list list is reversed
// in TransformFlipHorizontal the colors remain the same
//
let rec revThrees x = 
  if x = [] then
    []
  else 
    x.Tail.Tail.Head :: x.Tail.Head :: x.Head :: revThrees (x.Tail.Tail.Tail)

//--------------------------------------------------------------------------------TransformFlipHorizontal---//
// flips picture from left to right and uses the recursive function revThrees
let rec TransformFlipHorizontal(width:int, height:int, depth:int, image:int list list) = 
  
  let unOrderedReverse = List.map(fun x-> revThrees x ) image
  let horizontalImage = List.map(fun x -> List.rev x) unOrderedReverse

  horizontalImage
  

//----------------------------------------------------------------------------------TransformFlipVertical---//
// flips picture from bottom to top
let rec TransformFlipVertical(width:int, height:int, depth:int, image:int list list) = 
  
  let verticalImage = List.rev image 
  
  verticalImage
  


//
// make list of ints into list of tuples holding (r,g,b)
//
let rec getTuples x =
  if x = [] then
    []
  else
    (x.Head,x.Tail.Head,x.Tail.Tail.Head) :: getTuples x.Tail.Tail.Tail

//
// iterate through each list and aligning each tuple of the same index into one list
//
let rec getIndexLists L =   
  if (List.head L) = [] then
    []
  else
    let indexList = List.map (fun x -> List.head x) L // getting head of each colomn
    indexList :: getIndexLists (List.map (fun x -> List.tail x) L) // attaching head to next column head
  
//
// revert the list of tuples back into a list of ints
//
let rec getList L = 
  if L = [] then
    []
  else
    let r,g,b = L.Head 
    r::g::b::getList L.Tail


//------------------------------------------------------------------------------------------RotateRight90---//
// rotates an image by 90 degrees to the right
let rec RotateRight90(width:int, height:int, depth:int, image:int list list) = 
  if image = [] then
    []
  else   
    //to make rgb manipulation easier they get grouped into a list tuples here
    let tuples = List.map (fun x -> getTuples x) image     
    // create lists by making lists of same index tuples of various row lists
    let matchingIndexList = getIndexLists tuples    
    // currently rotates to the left therefore reversing list to rotate right
    let reverseList = List.map(fun x-> List.rev x) matchingIndexList
    // revert back to int list list from tuple list list
    let image90 = List.map(fun x-> getList x)reverseList   

    image90

  
  
  
  