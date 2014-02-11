public class OS_0912_2 {
	public static void main(String[] args){
		long distance = (long)410121021 * 100;
		long count = 0;

		while(distance>0){
			count++;
			distance -= (int)(Math.random()*101);
		}
		System.out.println(count);
	}
}
