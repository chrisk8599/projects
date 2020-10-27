public class run{
	public static void main(String[] args){
		EspressOSMobile phone = new EspressOSMobile();
		System.out.println(phone.isPhoneOn());
		phone.setPhoneOn(true);
		EspressOSContact con = phone.getCopyOfOwnerContact();
		con.addChatMessage("Angus", "Man, I'm so hungry! Can you buy me a burrito?");
		System.out.println(con.getLastMessage());	
		con.addChatMessage("Beatrice", "I don't have any money to buy you a burrito.");
		System.out.println(con.getLastMessage());	
		con.addChatMessage("Angus", "Please? I haven't eaten anything all day.");
			System.out.println(con.getLastMessage());	

		
 // *
 // *   	getLastMessage() returns "Angus: Please? I haven't eaten anything all day."
 // *   	getOldestMessage() returns "Angus: Man, I'm so hungry! Can you buy me a burrito?"
	}
}
