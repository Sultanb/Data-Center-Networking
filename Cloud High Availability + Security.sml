(*Security-In case someone tried to access the infrastrcture*)
val cbs: (int -> unit) list ref = ref []
fun onKeyEvent f = cbs := f :: (!cbs)
fun onEvent i =
    let fun loop fs =
	    case fs of
		[] => ()
	      | f::fs' => (f i; loop fs')
    in
	loop (!cbs)
    end
(* Pattern match the packets including VXLAN header *)
fun append (xs,ys)
	   case xs of
	       [] => ys
	     | xs::xs' => x::append(xs',ys)
(* Availability-MTBF,convergence time, Resilience 2ms *)
fun Avail xs = fold ((fn(MTBF,CT) => MTBF<=2 andalso CT<=2),true,xs)

(* Scale In/Out - KPI Measurements Min=20% Max=80% *)
fun Scalein xs = fold ((fn(KPI1,KPI2) => KPI1<=20 andalso KPI2<=20),true,xs)
fun scaleout xs = fold ((fn(KPI1,KPI2) => KPI1>=80 andalso KPI2>=80),true,xs)
