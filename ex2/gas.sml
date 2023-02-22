fun get_adjacent [] cityA visited = []            (*Get not visited adjacent cities from cityA*)
 |  get_adjacent ((city1, city2, dist) ::roads) (cityA:int) visited =       (*We annotate cityA as int so that*)
    if (city1 = cityA) then                                                 (*we don't get "calling polyEqual" warning*)
        if not (List.exists (fn x => x = city2) visited) then city2::(get_adjacent roads cityA visited)
                                                         else get_adjacent roads cityA visited
    else if (city2 = cityA) then
        if not (List.exists (fn x => x = city1) visited) then city1::(get_adjacent roads cityA visited)
                                                         else get_adjacent roads cityA visited
    else get_adjacent roads cityA visited

fun DFS visited roads start =                     (*Traverse graph from start*)
    let
      val adj_cities = get_adjacent roads start visited
      fun travel_to_adjacent [] = (start::visited)
       |  travel_to_adjacent (adj1::adj_rest) =
            DFS (travel_to_adjacent adj_rest) roads adj1       
    in
      travel_to_adjacent adj_cities
    end              

fun test_if_connected visited roads start (endd:int) =                    (*Check if the graph with nodes in road_list is connected,*)
    (List.exists (fn x => x = endd) (DFS visited roads start))       (*if we can traven from start to endd*)

fun mergeSort nil = nil
 |  mergeSort [e] = [e]          
 |  mergeSort theList =
        let
            fun halve nil = (nil, nil)
              | halve [a] = ([a], nil)
              | halve (a::b::cs) =
                let
                    val (x, y) = halve cs
                in
                    (a::x, b::y)
                end

            fun merge (nil, ys) = ys
              | merge (xs, nil) = xs
              | merge ((x1,x2,xd) :: xs, (y1,y2,yd) :: ys) =
                if xd > yd then (x1,x2,xd) :: merge(xs, (y1,y2,yd) :: ys)    (*We compare the distance of the roads*)
                           else (y1,y2,yd) :: merge((x1,x2,xd) :: xs, ys)

            val (x, y) = halve theList
        in
            merge (mergeSort x, mergeSort y)
        end

fun readint filename =                         (*Read the file, gets input in int list*)
    let
        val ins = TextIO.openIn filename
        fun loop ins =
            case TextIO.scanStream (Int.scan StringCvt.DEC) ins of
                SOME int => int :: loop ins
            |   NONE => []
    in
        loop ins
    end

fun get_sorted_road_list filename =            (*Creates road list from input, sorts it*)                  
    let 
        val (hd1::hd2::tail) = readint filename
        val cities = hd1
        val roads = hd2
        fun add_road_to_list [] = []
        |   add_road_to_list (ct1::ct2::dist::tl) = (ct1, ct2, dist)::(add_road_to_list tl)
        |   add_road_to_list _ = []                               (*So that we don't have match nonexhaustive*)
    in
        mergeSort (add_road_to_list tail)                         (*Sort in descending order*)
    end

fun min_fill filename = 
    let 
        val roadslist = get_sorted_road_list filename
        fun find_min_fill [] = 0                                                 (*So that we don't have match nonexhaustive*)                                 
         |  find_min_fill ((cityA, cityB, lngst_roadLength) :: roads) =          (*Try to remove longest road if graph is still connected*)
                if (test_if_connected [] roads cityA cityB) then find_min_fill roads (*Return longest road length in the MST*)
                                                            else lngst_roadLength
        val minFill = find_min_fill roadslist
    in TextIO.print (Int.toString minFill); TextIO.print "\n"
    end