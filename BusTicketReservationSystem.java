// BusTicketReservationSystem.java

import java.util.*;

public class BusTicketReservationSystem {
    static Scanner scanner = new Scanner(System.in);
    static List<Bus> buses = new ArrayList<>();
    static int ticketNumber = 15324;
    static int routeCounter = 1;
    static final int MAX_SEATS = 10;

    static String[] cities = {
        "CHENNAI", "BENGALURU", "MUMBAI", "DELHI", "KOLKATA", "PUNJAB", "GUJARAT"
    };

    public static void main(String[] args) {
        while (true) {
            displayMenu();
            int choice = getIntInput("Enter your choice: ");
            switch (choice) {
                case 1:
                    bookTickets();
                    break;
                case 2:
                    cancelTicket();
                    break;
                case 3:
                    checkTicketAvailability();
                    break;
                case 4:
                    checkTicketDetails();
                    break;
                case 5:
                    markSeatForExchange();
                    break;
                case 6:
                    transferSeat();
                    break;
                case 7:
                    checkExchangeableSeats();
                    break;
                case 8:
                    System.out.println("Thank you for using the Bus Ticket Reservation System.");
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    static void displayMenu() {
        System.out.println("\n--- Bus Ticket Reservation System ---");
        System.out.println("1. Book Tickets");
        System.out.println("2. Cancel Ticket");
        System.out.println("3. Check Ticket Availability");
        System.out.println("4. Check Ticket Details");
        System.out.println("5. Mark Seat for Exchange");
        System.out.println("6. Transfer Seat");
        System.out.println("7. Check Exchangeable Seats");
        System.out.println("8. Exit");
    }

    static void bookTickets() {
        displayCities();
        int source = getIntInput("Enter source city code: ");
        int destination = getIntInput("Enter destination city code: ");
        if (source == destination || source < 0 || destination < 0 || source >= cities.length || destination >= cities.length) {
            System.out.println("Invalid source or destination.");
            return;
        }

        int routeNumber = routeCounter++;
        int busNumber = (routeNumber * 100) + (destination * 10) + source;

        Bus bus = findOrCreateBus(busNumber, source, destination);
        bus.displayAvailableSeats();

        int numberOfTickets = getIntInput("Enter number of tickets to book: ");
        for (int i = 0; i < numberOfTickets; i++) {
            int seatNumber = getIntInput("Choose your seat number: ");
            if (seatNumber < 1 || seatNumber > MAX_SEATS) {
                System.out.println("Invalid seat number.");
                i--;
                continue;
            }
            if (bus.isSeatReserved(seatNumber)) {
                System.out.println("Seat already reserved. Choose another seat.");
                i--;
                continue;
            }
            scanner.nextLine(); // Consume newline
            System.out.print("Enter passenger name: ");
            String name = scanner.nextLine();
            int age = getIntInput("Enter passenger age: ");
            System.out.print("Enter mobile number: ");
            String mobileNumber = scanner.nextLine();

            Passenger passenger = new Passenger(name, age, mobileNumber);
            bus.reserveSeat(seatNumber, passenger);
            generateBill(busNumber, seatNumber, passenger);
        }
    }

    static void cancelTicket() {
        int busNumber = getIntInput("Enter your bus number: ");
        int seatNumber = getIntInput("Enter your seat number: ");
        Bus bus = findBus(busNumber);
        if (bus != null && bus.isSeatReserved(seatNumber)) {
            bus.cancelSeat(seatNumber);
            System.out.println("Ticket canceled successfully.");
        } else {
            System.out.println("No reservation found for the given details.");
        }
    }

    static void checkTicketAvailability() {
        displayCities();
        int source = getIntInput("Enter source city code: ");
        int destination = getIntInput("Enter destination city code: ");
        if (source == destination || source < 0 || destination < 0 || source >= cities.length || destination >= cities.length) {
            System.out.println("Invalid source or destination.");
            return;
        }

        int routeNumber = routeCounter++;
        int busNumber = (routeNumber * 100) + (destination * 10) + source;

        Bus bus = findOrCreateBus(busNumber, source, destination);
        bus.displayAvailableSeats();
    }

    static void checkTicketDetails() {
        int busNumber = getIntInput("Enter your bus number: ");
        int seatNumber = getIntInput("Enter your seat number: ");
        Bus bus = findBus(busNumber);
        if (bus != null && bus.isSeatReserved(seatNumber)) {
            Passenger passenger = bus.getPassenger(seatNumber);
            System.out.println("Bus Number: " + busNumber);
            System.out.println("Seat Number: " + seatNumber);
            System.out.println("Passenger Name: " + passenger.name);
            System.out.println("Passenger Age: " + passenger.age);
            System.out.println("Mobile Number: " + passenger.mobileNumber);
        } else {
            System.out.println("No reservation found for the given details.");
        }
    }

    static void markSeatForExchange() {
        int busNumber = getIntInput("Enter your bus number: ");
        int seatNumber = getIntInput("Enter your seat number: ");
        Bus bus = findBus(busNumber);
        if (bus != null && bus.isSeatReserved(seatNumber)) {
            bus.markSeatForExchange(seatNumber);
            System.out.println("Seat marked for exchange.");
        } else {
            System.out.println("No reservation found for the given details.");
        }
    }

    static void transferSeat() {
        int busNumber = getIntInput("Enter your bus number: ");
        int oldSeatNumber = getIntInput("Enter your current seat number: ");
        int newSeatNumber = getIntInput("Enter your new seat number: ");
        Bus bus = findBus(busNumber);
        if (bus != null && bus.isSeatReserved(oldSeatNumber) && !bus.isSeatReserved(newSeatNumber)) {
            bus.transferSeat(oldSeatNumber, newSeatNumber);
            System.out.println("Seat transferred successfully.");
        } else {
            System.out.println("Seat transfer failed. Please check the seat numbers.");
        }
    }

    static void checkExchangeableSeats() {
        int busNumber = getIntInput("Enter your bus number: ");
        Bus bus = findBus(busNumber);
        if (bus != null) {
            bus.displayExchangeableSeats();
        } else {
            System.out.println("Bus not found.");
        }
    }

    static void displayCities() {
        System.out.println("Available Cities:");
        for (int i = 0; i < cities.length; i++) {
            System.out.println(i + ": " + cities[i]);
        }
    }

    static void generateBill(int busNumber, int seatNumber, Passenger passenger) {
        System.out.println("\n--- Ticket Details ---");
        System.out.println("Ticket Number: " + ticketNumber++);
        System.out.println("Bus Number: " + busNumber);
        System.out.println("Seat Number: " + seatNumber);
        System.out.println("Passenger Name: " + passenger.name);
        System.out.println("Passenger Age: " + passenger.age);
        System.out.println("Mobile Number: " + passenger.mobileNumber);
        System.out.println("Total Amount: ₹100");
        System.out.println("----------------------\n");
    }

    static Bus findBus(int busNumber) {
        for (Bus bus : buses) {
            if (bus.busNumber == busNumber) {
                return bus;
            }
        }
        return null;
    }

    static Bus findOrCreateBus(int busNumber, int source, int destination) {
        Bus bus = findBus(busNumber);
        if (bus == null) {
            bus = new Bus(busNumber, source, destination);
            buses.add(bus);
        }
        return bus;
    }

    static int getIntInput(String prompt) {
        System.out.print(prompt);
        while (!scanner.hasNextInt()) {
            System.out.print("Invalid input. " + prompt);
            scanner.next();
        }
        return scanner.nextInt();
    }
}

class Bus {
    int busNumber;
    int source;
    int destination;
    Map<Integer, Passenger> seatMap = new HashMap<>();
    Set<Integer> exchangeableSeats = new HashSet<>();

    Bus(int busNumber, int source, int destination) {
        this.busNumber = busNumber;
        this.source = source;
        this.destination = destination;
    }

    void reserveSeat(int seatNumber, Passenger passenger) {
        seatMap.put(seatNumber, passenger);
    }

    boolean isSeatReserved(int seatNumber) {
        return seatMap.containsKey(seatNumber);
    }

    void cancelSeat(int seatNumber) {
        seatMap.remove(seatNumber);
        exchangeableSeats.remove(seatNumber);
    }

    Passenger getPassenger(int seatNumber) {
        return seatMap.get(seatNumber);
    }

    void markSeatForExchange(int seatNumber) {
        if (isSeatReserved(seatNumber)) {
            exchangeableSeats.add(seatNumber);
        }
    }

    void transferSeat(int oldSeatNumber, int newSeatNumber) {
        Passenger passenger = seatMap.remove(oldSeatNumber);
        seatMap.put(newSeatNumber, passenger);
        if (exchangeableSeats.contains(oldSeatNumber)) {
            exchangeableSeats.remove(oldSeatNumber);
            exchangeableSeats.add(newSeatNumber);
        }
    }

    void displayAvailableSeats() {
        System.out.println("Available Seats:");
        for (int i = 1; i <= BusTicketReservationSystem.MAX_SEATS; i++) {
            if (!isSeatReserved(i)) {
                System.out.println("Seat " + i + ": Available");
            } else {
                System.out.println("Seat " + i + ": Reserved");
            }
        }
    }

    void displayExchangeableSeats() {
        System.out.println("Exchangeable
::contentReference[oaicite:25]{index=25}
 
