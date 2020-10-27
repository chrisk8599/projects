import java.util.*;
import java.io.*;

/**
 * EspressOS Mobile Phone Class.
 *
 *
 * EspressOSMobile
 * In this assignment you will be creating an EspressOS Mobile Phone as part of a simulation.
 * The Mobile phone includes several attributes unique to the phone and has simple functionality.
 * You are to complete 2 classes. EspressOSMobile and EspressOSContact
 *
 * The phone has data
 *  Information about the phone state. 
 *    If it is On/Off
 *    Battery level 
 *    If it is connected to network. 
 *    Signal strength when connected to network
 *  Information about the current owner saved as contact information. 
 *    First name
 *    Last name
 *    Phone number
 *  A list of 10 possible contacts.
 *    Each contact stores first name, last name, phone number and chat history up to 20 messages
 *  
 * The phone has functionality
 *  Turning on the phone
 *  Charging the phone. Increase battery level
 *  Change battery (set battery level)
 *  Use phone for k units of battery (decreases battery level by k)
 *  Search/add/remove contacts
 *
 * Attribute features
 *  if the phone is off. It is not connected. 
 *  if the phone is not connected there is no signal strength
 *  the attribute for battery life has valid range [0,100]. 0 is flat, 100 is full.
 *  the attribute for signal strength has a valid range [0, 5]. 0 is no signal, 5 is best signal.
 * 
 * Please implement the methods provided, as some of the marking is
 * making sure that these methods work as specified.
 *
 *
 */
public class EspressOSMobile 
{
	public static final int MAXIMUM_CONTACTS = 10;
	protected int batteryLife ;
	
	protected boolean phoneOn ;
	protected int countContacts = 0;
	protected int signalStrength ;
	protected boolean networkConnected ;
	protected EspressOSContact owner;
	/* Use this to store contacts. Do not modify. */
	protected EspressOSContact[] contacts;
	protected ArrayList<EspressOSContact> search;
	protected EspressOSContact[ ] found;
	protected ArrayList<Apps> applications;
	protected Apps[] runApps;

// 	/* Every phone manufactured has the following attributes
// 	 * 
// 	 * the phone is off
// 	 * the phone has battery life 25
// 	 * the phone is not connected
// 	 * the phone has signal strength 0
// 	 * Each of the contacts stored in the array contacts has a null value
// 	 * 
// 	 * the owner first name "EspressOS"
// 	 * the owner last name is "Incorporated"
// 	 * the owner phone number is "180076237867"
// 	 * the owner chat message should have only one message 
// 	 *         "Thank you for choosing EspressOS products"
// 	 *
// 	 *//
	
	
	public EspressOSMobile() {
		/* given */
		this.signalStrength = 0;
		this.phoneOn = false;
		this.networkConnected = false;
		this.batteryLife = 25;
		contacts = new EspressOSContact[MAXIMUM_CONTACTS];
		owner = new EspressOSContact("EspressOS","Incorporated","180076237867");
		owner.addChatMessage("EspressOS","Thank you for choosing EspressOS products");
		applications  = new ArrayList<Apps>();
		runApps = new Apps[30];
	}

	/* returns a copy of the owner contact details
	 * return null if the phone is off
	 */
	public EspressOSContact getCopyOfOwnerContact() {
		if (phoneOn){
			
			return owner.copy();
		}
	
			return null;
	
	
	}


	/* only works if phone is on
	 * will add the contact in the array only if there is space and does not exist
	 * The method will find an element that is null and set it to be the contact
	 */
	public boolean addContact(EspressOSContact contact) {
		if(isPhoneOn()){
			if (contacts.length > 11){
				return false;
			}
			else {
				for(EspressOSContact con : contacts){
					if (con == (contact)){
						return false;
					}
					
				}
				
				for(int i= 0 ; i<contacts.length;i++){
					if (contacts[i]== null){
						contacts[i] = contact;
						return true;
					}
					
				}
				
			}
		}
	
			return false;
	
	}

	/* only works if phone is on
	 * find the object and set the array element to null
 	 * return true on successful remove
	 */
	public boolean removeContact(EspressOSContact contact) {
		if (isPhoneOn()){
			
			if(contact == null){
				return false;
			}
			
			for(int i=0; i<contacts.length ; i++){
				if(contacts[i] == (contact)){
					contacts[i] = null;
				}
			}
			
			
			
			return true;
		}
		else{
			return false;

		}
	}

	/* only works if phone is on
	 * return the number of contacts, or -1 if phone is off
	 */
	public int getNumberOfContacts() {
		int noCount = 0;
		if (isPhoneOn()){
			for (int i=0;i<contacts.length;i++){
				if (contacts[i] != null){
					noCount+=1;
				}
			}
			return noCount;
		}
		return -1;
	}

	/* only works if phone is on
	 * returns all contacts that match firstname OR lastname
	 * if phone is off, or no results, null is returned
	 */
	public EspressOSContact[] searchContact(String name) {
		if(phoneOn){
			
			search  = new ArrayList<EspressOSContact>();
			for(int i= 0 ; i<contacts.length;i++){
				if (contacts[i]!= null){
				if(contacts[i].getFirstName()==name ||contacts[i].getLastName()==name){
					search.add(contacts[i]);
					
				
				}
			}
			}
			if (search.size()>0){
				found = new EspressOSContact[search.size()];
				for(int i=0;i<search.size();i++){
					found[0] = search.get(i);
				}
				return found;
			
			}
			
		}
		return null;
	}

	/* returns true if phone is on
	 */
	public boolean isPhoneOn() {
		if(phoneOn){
			return true;
		}
		else{return false;}

	}

	/* when phone turns on, it costs 5 battery for startup. network is initially disconnected
	 * when phone turns off it costs 0 battery, network is disconnected
	 * always return true if turning off
	 * return false if do not have enough battery level to turn on
	 * return true otherwise
	 */
	 public boolean setPhoneOn(boolean on) {
		 if (on && this.batteryLife < 6){
			 return false;
			 
		 }
		 else if(on && this.batteryLife > 5){
			 phoneOn = true;
			 usePhone(5);
			 networkConnected = false;
			 return true;
		 }
		 else if(!on){
			 phoneOn = false;
			 networkConnected = false;
			 return true;
		 }
		 
		 return false;
		 
		
	}
	
	/* Return the battery life level. if the phone is off, zero is returned.
	 */
	public int getBatteryLife() {
		if (!phoneOn){
			this.batteryLife = 0;
			return this.batteryLife;
		}
		else{
			return this.batteryLife;
		}

	}
	
	/* Change battery of phone.
	 * On success. The phone is off and new battery level adjusted and returns true
	 * If newBatteryLevel is outside manufacturer specification of [0,100], then 
	 * no changes occur and returns false.
	 */
	public boolean changeBattery(Battery battery) {
		if(battery.getLevel()<0 || battery.getLevel()>100){
			return false;
		}
		else{
				batteryLife = battery.getLevel();
				phoneOn = false;
				return true;
		
		}
	

	}
	
	/* only works if phone is on. 
	 * returns true if the phone is connected to the network
	 */
	public boolean isConnectedNetwork() {
		if(phoneOn){
			if(networkConnected && (0<signalStrength)&& (6>signalStrength)){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}

	}
	
	/* only works if phone is on. 
	 * when disconnecting, the signal strength becomes zero
	 */
	public void disconnectNetwork() {
		if(phoneOn){
			signalStrength = 0;
			networkConnected = true;
		}

	}
	
	/* only works if phone is on. 
	 * Connect to network
	 * if already connected do nothing
	 * if connecting: 
	 *  1) signal strength is set to 1 if it was 0
	 *  2) signal strength will be the previous value if it is not zero
	 *  3) it will cost 2 battery life to do so
	 * returns the network connected status
	 */
	public boolean connectNetwork() {
		if (phoneOn){
			if(this.batteryLife < 3){
				usePhone(2);
				return false;
			}
			if(networkConnected && signalStrength>0){
				return true;
			}
			else{
				networkConnected = true;
				usePhone(2);
				if(signalStrength == 0){
					signalStrength = 1;
					
					return true;
				}
				else{
					
					return true;
				}
			}
			
			
		}
		else{
			return false;
		}

	}
	
	/* only works if phone is on. 
	 * returns a value in range [1,5] if connected to network
	 * otherwise returns 0
	 */
	public int getSignalStrength() {
		if (phoneOn){
			if((0<signalStrength) && networkConnected && (6>signalStrength)){
				return signalStrength;
			}
			else{
				return 0;
			}
		}
		else{
			return 0;
		}

	}

	/* only works if phone is on. 
	 * sets the signal strength and may change the network connection status to on or off
	 * signal of 0 disconnects network
	 * signal [1,5] can connect to network if not already connected
	 * if the signal is set outside the range [0,5], nothing will occur and will return false
	 */
	public boolean setSignalStrength(int x) {
		if(phoneOn){
			if(x==0){
				signalStrength = x;
				networkConnected = false;
				return true;
			}
			else if (x>0 && x<6){
				networkConnected = true;
				signalStrength = x;
				return true;
			}
			else{
				return false;
			}
				
		
		
			
		
    }
		return false;
	}
	
	/* changes the antenna object
	 * signal strength is set to default and is not connected to a network
	 * if this constraint is violated then the antenna should not be changed.
	 * return true if antenna is changed.
	 */
	public boolean changeAntenna(Antenna antenna) {
		
		if (phoneOn){
			if(signalStrength<0 && signalStrength>5){
				return false;
			}
		this.networkConnected = false;
		
		if(batteryLife>0){
			networkConnected = true;
			usePhone(2);
		}
		
		if(networkConnected){
			if(antenna.getSignalStrength() > 0 ){
				setSignalStrength(antenna.getSignalStrength());
				return true;
				
				
			}
			networkConnected = false;
			return true;
		}
			return false;
		}
		
	
		
		return false;
		
		
	}
	
	/* each charge increases battery by 10
	 * the phone has overcharge protection and cannot exceed 100
	 * returns true if the phone was charged by 10
	 */
	public boolean chargePhone() {
		
		if ((batteryLife + 10) > 100){
			batteryLife = 100;
			return false;
		}
		else{
			batteryLife += 10;
			return true;
		}

	}
	
	
	/* Use the phone which costs k units of battery life.
	 * if the activity exceeds the battery life, the battery automatically 
	 * becomes zero and the phone turns off.
	 */
	public void usePhone(int k) {	
		
		if(k>=this.batteryLife){
			this.batteryLife =0;
			phoneOn = false;
		}
		else if(this.batteryLife > k){
			this.batteryLife -= k;
		}

	}

	public boolean install(Apps app){
		if(app == null){
			return false;
		}
		for(Apps a : applications){
			if (a == app){
				return false;
			}
		}
		applications.add(app);
		return true;
		
	}
	
	public boolean uninstall(Apps app){
		if(app == null){
			return false;
		}
		for(Apps a : applications){
			if (a == app){
				applications.remove(a);
				return true;
			}
		}
		return false;
		
	}
	public Apps[] getRunningApps(){
		return runApps;
	}
	public Apps[] getInstalledApps (){
		Apps[] installedApps = new Apps[applications.size()];
		for(int i =0; i <applications.size(); i++){
			installedApps[i] = applications.get(i);
		}
		return installedApps;
	}

	
	
	
	
	
	
	
}

