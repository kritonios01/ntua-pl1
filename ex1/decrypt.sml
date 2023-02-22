(* Entropy is -S(fNc * logfc) = -S(Nc * logfc) / total_letters, where Nc is the number of letters c. 
   Since we want the string that minimizes the entropy, and all 26 strings have the same total letter count, 
   we can ignore the {/ total letters} factor and simply compute the sum of (-logfc) for every letter in our string *)

val fc = [0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
          0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
          0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
          0.00978, 0.02360, 0.00150, 0.01974, 0.00074]

val logfc = map (fn x => ~ (Math.ln x)) fc

fun letter_entropy c dist = 
    let
      val char_indx = Char.ord c - Char.ord #"a"
      val moved_char = (char_indx + dist) mod 26
    in
      List.nth (logfc, moved_char)
    end
    
fun char_entropy c dist = 
    case Char.isAlpha c of  
        true  => letter_entropy (Char.toLower c) dist
    |   false => 0.0

fun entropy [] dist = 0.0                              (*dist: 0...25 is the distance for ROTN*)
 |  entropy (c::t) dist = char_entropy c dist + entropy t dist

fun entropy_calc message entropy_list 0 = entropy_list         (*We get the list: [entropy(dist = 0), entropy(1), ... , entropy(25)*)
 |  entropy_calc message entropy_list n = entropy_calc message ((entropy message (n-1))::entropy_list) (n-1)

fun min [] = raise Empty
 |  min [x] = x
 |  min (h::t) = Real.min (h, min t)

fun index x (h::t) =  
    if Real.== (x,h) then 0 else 1 + index x t

val min_index = fn list => index (min list) list

fun shift_distance message = 
    min_index (entropy_calc message [] 26)

fun decode_character char dist = 
    if Char.isUpper char      then Char.chr ((Char.ord char - Char.ord #"A" + dist) mod 26 + Char.ord #"A")
    else if Char.isLower char then Char.chr ((Char.ord char - Char.ord #"a" + dist) mod 26 + Char.ord #"a")
    else char

fun decode message_string = 
    let
      val message = explode message_string
      val shift_dist = shift_distance message
      val dec_char = fn char => decode_character char shift_dist
      val decoded_char_list = map dec_char message
    in
      implode decoded_char_list
    end

fun read_file filename =
    TextIO.inputAll (TextIO.openIn filename)

fun decrypt filename = 
    TextIO.print (decode (read_file filename)^"\n")
