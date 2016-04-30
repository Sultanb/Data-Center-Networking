// * Affinity/Anti-Affinity Rules
interface Func<B,A> {
    B m(A x);
}
interface Pred<A> {
    boolean m(A x);
}

class List<T> {
    T       head;
    List<T> tail;
    List(T x, List<T> xs) {
	head = x;
	tail = xs;
    }

// * Anti Affinity xs list is a cluster of VMs for specific application
    static <A,B> List<B> map(Func<B,A> f, List<A> xs) {
	if(xs==null)
	    return null;
	return new List<B>(f.m(xs.head), map(f,xs.tail));
    }
// * Content Filtering - xs is a list of content
    static <A> List<A> filter(Pred<A> f, List<A> xs) {
	if(xs==null)
	    return null;
	if(f.m(xs.head))
	    return new List<A>(xs.head, filter(f,xs.tail));
	return filter(f,xs.tail);
    }
