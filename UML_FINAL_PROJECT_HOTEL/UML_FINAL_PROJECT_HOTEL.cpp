using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using System.Text;
using System.Threading.Tasks;

//Noor Omar Burini --> 136799
//Lina Mohamed Al-Dwairi --> 136729
//REEM MOHAMMAD A.ALBELBISI --> 146902

namespace uml_project
{
    [Serializable]
    class customer
    {
        private string name;
        private string password;
        private double credit;
        private booking[] booking_related_customer = new booking[100];
        private system s = new system();
        int BSize = 0;
        hotel h = new hotel();
        public customer()
        {
            name = "";
            password = "";
            credit = 0;
        }
        public customer(string name, string password, double credit)
        {
            this.name = name;
            this.password = password;
            this.credit = credit;
        }
        public string getName()
        {
            return name;
        }
        public string getPass()
        {
            return password;
        }
        public double getCredit()
        {
            return credit;
        }
        public bool log_in(string name, string password)
        {
            bool f = false;
            for (int i = 0; i < s.get_cSize(); i++)
            {
                if (s.getCnames(i) == name && s.GetPass(i) == password)
                {
                    f = true;
                    Console.WriteLine("** HI , Welcome " + name + " **");
                    this.name = name;
                    this.password = password;
                    credit = s.getCcredit(i);
                    break;
                }
            }
            if (f == false)
            {
                Console.WriteLine("** Wrong username or password **");
            }
            return f;
        }
        public void make_booking(string ID)
        {
            Console.WriteLine("Please enter the hotel class : ");
            string hcl = Console.ReadLine();
            Console.WriteLine("Please enter the hotel location : ");
            string hlo = Console.ReadLine();
            if (s.display_matched_hotels(hcl, hlo) == true)
            {
                Console.WriteLine("Please enter the hotel name : ");
                string hna = Console.ReadLine();

                Console.WriteLine("Please enter the number of rooms : ");
                int nr = Convert.ToInt32(Console.ReadLine());

                Console.WriteLine("Please enter the type of meal A or B : ");
                char tm = Convert.ToChar(Console.ReadLine());

                Console.WriteLine("Please enter the number of days : ");
                int nd = Convert.ToInt32(Console.ReadLine());

                double c = 0;

                s.add_booking(ID, name, hna, nr, nd, tm, c);

                booking B = new booking(ID, name, hna, nr, nd, tm, c);

                booking_related_customer[BSize] = B;

                c = booking_related_customer[BSize].bookingCost(hna);

                booking_related_customer[BSize].setCost(c);

                BSize++;
            }
        }
        public void view_my_bookings()
        {
            if (BSize != 0)
            {
                for (int i = 0; i < BSize; i++)
                {
                    Console.Write("Booking ID : ");
                    Console.WriteLine(booking_related_customer[i].getID());
                    Console.WriteLine();
                    Console.Write("Customer Name : ");
                    Console.WriteLine(name);
                    Console.WriteLine();
                    Console.Write("Hotel Name : ");
                    Console.WriteLine(booking_related_customer[i].getHotelName());
                    Console.WriteLine();
                    Console.Write("Status : ");
                    if (booking_related_customer[i].getStatus() == false)
                        Console.WriteLine("Not completed");
                    else
                        Console.WriteLine("Completed");
                    Console.WriteLine();
                    Console.Write("Number of days : ");
                    Console.WriteLine(booking_related_customer[i].getNumofDays());
                    Console.WriteLine();
                    Console.Write("Number of rooms : ");
                    Console.WriteLine(booking_related_customer[i].getNumofRooms());
                    Console.WriteLine();
                    Console.Write("Meal Type : ");
                    Console.WriteLine(booking_related_customer[i].getMealType());
                    Console.WriteLine();
                    Console.Write("Bookings cost : ");
                    Console.WriteLine(booking_related_customer[i].getCost());
                    Console.WriteLine();
                }
            }
            else
            {
                Console.WriteLine("There are No bookings yet");
            }
        }
        public void cancel_booking(string ID)
        {
            s.delete_booking(ID);
            bool f = false;
            int tempsize = BSize;
            var bList = booking_related_customer.ToList();
            for (int i = 0; i < tempsize; i++)
            {
                if (booking_related_customer[i].getID() == ID)
                {
                    f = true;
                    bList.Remove(booking_related_customer[i]);
                    BSize--;
                    Console.WriteLine("The booking with ID " + ID + " is canceled successfully");
                }
            }
            if (f == false)
            {
                Console.WriteLine("There is No booking in the system matches the ID you entered");
            }
            else
            {
                booking_related_customer = bList.ToArray();
            }
        }
        public void pay()
        {
            bool f = false;
            if (BSize != 0)
            {
                for (int i = 0; i < BSize; i++)
                {
                    if (booking_related_customer[i].getStatus() == false)
                    {
                        f = true;
                        Console.WriteLine("These are all Not completed bookings");
                        Console.Write("Booking ID : ");
                        Console.WriteLine(booking_related_customer[i].getID());
                        Console.WriteLine();
                        Console.Write("Customer Name : ");
                        Console.WriteLine(name);
                        Console.WriteLine();
                        Console.Write("Hotel Name : ");
                        Console.WriteLine(booking_related_customer[i].getHotelName());
                        Console.WriteLine();
                        Console.Write("Status : ");
                        Console.WriteLine("Not completed");
                        Console.WriteLine();
                        Console.Write("Number of days : ");
                        Console.WriteLine(booking_related_customer[i].getNumofDays());
                        Console.WriteLine();
                        Console.Write("Number of rooms : ");
                        Console.WriteLine(booking_related_customer[i].getNumofRooms());
                        Console.WriteLine();
                        Console.Write("Meal Type : ");
                        Console.WriteLine(booking_related_customer[i].getMealType());
                        Console.WriteLine();
                        Console.Write("Bookings cost : ");
                        Console.WriteLine(booking_related_customer[i].getCost());
                        Console.WriteLine();
                    }
                }
                if (f == false)
                {
                    Console.WriteLine("All bookings in the system are completed");
                    return;
                }
                Console.WriteLine("Please enter the ID of the booking you want to pay");
                string id = Console.ReadLine();
                for (int i = 0; i < BSize; i++)
                {
                    if (booking_related_customer[i].getID() == id)
                    {
                        string hn = booking_related_customer[i].getHotelName();
                        double b = booking_related_customer[i].getCost();
                        if (credit >= b)
                        {
                            credit = credit - b;
                            booking_related_customer[i].setStatuse(true);
                            Console.WriteLine("you completed this booking with ID = " + id + " successfully ");
                        }
                        else
                        {
                            Console.WriteLine("your credit is not enough to pay this booking");
                        }
                    }
                }
            }
            else
            {
                Console.WriteLine("There is no bookings to pay for it yet");
            }
        }
    }

    [Serializable]
    class administrator
    {
        string name;
        string pass;
        system s = new system();
        public bool log_in(string name, string pass)
        {
            bool flag = false;
            this.name = name;
            this.pass = pass;
            if (name == "admin" && pass == "111")
            {
                Console.WriteLine("** Hi, Welcome Administrator **");
                flag = true;
            }
            else
                Console.WriteLine("** Wrong username or password **");
            return flag;
        }
        public void add_hotel()
        {
            Console.WriteLine("Please enter hotel name : ");
            string n = Console.ReadLine();

            Console.WriteLine("Please enter hotel classification : ");
            string c = Console.ReadLine();

            Console.WriteLine("Please enter hotel location : ");
            string l = Console.ReadLine();

            Console.WriteLine("Please enter daily cost per one room with breakfast :  ");
            string CostB = Console.ReadLine();
            double costB = Convert.ToDouble(CostB);

            Console.WriteLine("Please enter daily cost per one room with all meals :  ");
            string costA = Console.ReadLine();
            double costAll = Convert.ToDouble(costA);

            Console.WriteLine("Please enter number of available rooms : ");
            string r = Console.ReadLine();
            int rooms = Convert.ToInt32(r);

            Console.WriteLine("Please enter total income : ");
            string i = Console.ReadLine();
            double income = Convert.ToDouble(i);

            Console.WriteLine("Please enter the discount : ");
            string d = Console.ReadLine();
            double discount = Convert.ToDouble(d);

            s.add_Hotel(n, c, l, costB, costAll, rooms, income, discount);
        }
        public void add_customer(string name)
        {
            Console.WriteLine("Please enter password : ");
            string pass = Console.ReadLine();


            Console.WriteLine("Please enter credit : ");
            int credit = Convert.ToInt32(Console.ReadLine());

            s.add_Customer(name, pass, credit);
        }
        public void update_hotel_info()
        {
            Console.WriteLine("Please enter name of the hotel you want to update");
            string hname = Console.ReadLine();
            s.update_hotel_info(hname);
        }
        public void delete_hotel()
        {
            s.delete_hotel();
        }
        public void view(char v)
        {
            if (v == 'h')
                s.view_hotels();
            else if (v == 'c')
                s.view_customers();
            else if (v == 'b')
                s.view_bookings();
        }
        public void view_all_bookings_related_to_specific_hotel(string hotel_name)
        {

        }
    }
    [Serializable]
    class hotel
    {
        private string name;
        private string classification;
        private double daily_cost_breakfast;
        private double daily_cost_all_meals;
        private int num_of_available_rooms;
        private double discount;
        private double income;
        public booking[] booking_related_hotel;
        private string location;
        int bhSize = 0;
        public hotel()
        {

        }
        public hotel(string n, string c, string l, double costB, double costAll, int rooms, double income, double d)
        {
            name = n;
            classification = c;
            location = l;
            daily_cost_breakfast = costB;
            daily_cost_all_meals = costAll;
            num_of_available_rooms = rooms;
            this.income = income;
            discount = d;
        }
        public string getName()
        {
            return name;
        }
        public string getClass()
        {
            return classification;
        }
        public string getLocation()
        {
            return location;
        }
        public double getCostB()
        {
            return daily_cost_breakfast;
        }
        public double getCostAll()
        {
            return daily_cost_all_meals;
        }
        public int getNumofRooms()
        {
            return num_of_available_rooms;
        }
        public int getBHSize()
        {
            return bhSize;
        }
        public double getIncome()
        {
            return income;
        }
        public double getDiscount()
        {
            return discount;
        }
        public void setBHSize(int a)
        {
            bhSize = a;
        }
        public void setNumofRooms(int r)
        {
            num_of_available_rooms = r;
        }
        public void setCostB(double b)
        {
            daily_cost_breakfast = b;
        }
        public void setCostA(double a)
        {
            daily_cost_all_meals = a;
        }
        public void setDiscount(double d)
        {
            discount = d;
        }
    }

    [Serializable]
    class booking
    {
        private string id;
        private string customerName;
        private string hotelName;
        private bool status = false;
        private int numOfRooms;
        private char mealType;
        private int numOfDays;
        private double bookingsCost;
        hotel[] H = new hotel[1000];
        int hsize = 0;
        public booking(string id, string cn, string hn, int numOfRooms, int numOfDays, char meal, double bookingsCost)
        {
            this.id = id;
            customerName = cn;
            hotelName = hn;
            this.numOfRooms = numOfRooms;
            this.numOfDays = numOfDays;
            this.mealType = meal;
            this.bookingsCost = bookingsCost;
        }
        public double bookingCost(string hotelName)
        {
            double bcost = 0;
            int j = 0;
            FileStream fs2 = new FileStream("hotels.txt", FileMode.Open, FileAccess.Read);
            BinaryFormatter bf2 = new BinaryFormatter();
            while (fs2.Position < fs2.Length)
            {
                H[j] = (hotel)bf2.Deserialize(fs2);
                j++;
                hsize++;
            }
            fs2.Close();
            int y = 0;

            for (int i = 0; i < hsize; i++)
            {
                if (H[i].getName() == hotelName)
                {
                    y = i;
                }
            }

            if (mealType == 'B')
            {
                bcost = (numOfRooms) * ((numOfDays)*H[y].getCostB());

            }
            else if (mealType == 'A')
            {
                bcost = (numOfRooms) * (numOfDays)*H[y].getCostAll();
            }

            if (H[y].getDiscount() == 0)
            {
                double final_booking_cost_without_discount = bcost;
                return final_booking_cost_without_discount;
            }
            else
            {
                double final_booking_cost_with_discount = bcost - (bcost * H[y].getDiscount());
                return final_booking_cost_with_discount;
            }
        }
        public string getID()
        {
            return id;
        }
        public string getCustomerName()
        {
            return customerName;
        }
        public string getHotelName()
        {
            return hotelName;
        }
        public bool getStatus()
        {
            return status;
        }
        public char getMealType()
        {
            return mealType;
        }
        public int getNumofDays()
        {
            return numOfDays;
        }
        public double getCost()
        {
            return bookingsCost;
        }
        public int getNumofRooms()
        {
            return numOfRooms;
        }
        public void setStatuse(bool b)
        {
            status = b;
        }
        public void setCost(double c)
        {
            bookingsCost = c;
        }
    }

    [Serializable]
    class system
    {
        public hotel[] h = new hotel[1000];
        public customer[] c = new customer[1000];
        public booking[] b = new booking[1000];
        private int bSize = 0;
        private int hSize = 0;
        private int cSize = 0;
        hotel h1 = new hotel();
        public system()
        {
            if (File.Exists("customers.txt"))
            {
                FileStream fs1 = new FileStream("customers.txt", FileMode.Open, FileAccess.Read);
                BinaryFormatter bf1 = new BinaryFormatter();
                int i = 0;
                while (fs1.Position < fs1.Length)
                {
                    c[i] = (customer)bf1.Deserialize(fs1);
                    i++;
                    cSize++;
                }

                fs1.Close();
            }
            if (File.Exists("hotels.txt"))
            {
                FileStream fs2 = new FileStream("hotels.txt", FileMode.Open, FileAccess.Read);
                BinaryFormatter bf2 = new BinaryFormatter();
                int j = 0;
                while (fs2.Position < fs2.Length)
                {
                    h[j] = (hotel)bf2.Deserialize(fs2);
                    j++;
                    hSize++;
                }

                fs2.Close();
            }
        }
        public bool display_matched_hotels(string classification, string location)
        {
            bool f = false;
            for (int i = 0; i < hSize; i++)
            {
                if (h[i].getClass() == classification && h[i].getLocation() == location)
                {
                    f = true;
                    Console.WriteLine();
                    Console.WriteLine("Here are all hotels that matched with your choices");
                    Console.WriteLine();
                    Console.Write("hotel name: ");
                    Console.WriteLine(h[i].getName());
                    Console.WriteLine();
                    Console.Write("Classification: ");
                    Console.WriteLine(h[i].getClass());
                    Console.WriteLine();
                    Console.Write("Location: ");
                    Console.WriteLine(h[i].getLocation());
                    Console.WriteLine();
                    Console.Write("Daily cost per one room with breakfast : ");
                    Console.WriteLine(h[i].getCostB());
                    Console.WriteLine();
                    Console.Write("Daily cost per one room with all meals : ");
                    Console.WriteLine(h[i].getCostAll());
                    Console.WriteLine();
                    Console.Write("Number of available rooms : ");
                    Console.WriteLine(h[i].getNumofRooms());
                    Console.WriteLine();
                    Console.Write("Total income : ");
                    Console.WriteLine(h[i].getIncome());
                    Console.WriteLine();
                    Console.Write("Discount : ");
                    Console.WriteLine(h[i].getDiscount());
                    Console.WriteLine();

                }
            }
            if (f == false)
            {
                Console.WriteLine("There are No hotels matched your choices");
            }
            return f;
        }

        public void delete_hotel()
        {
            int tempsize = hSize;
            var hList = h.ToList();
            for (int i = 0; i < tempsize; i++)
            {
                if (h[i].getIncome() < 2000)
                {
                    hList.Remove(h[i]);
                    hSize--;
                }
            }
            h = hList.ToArray();
            Console.WriteLine("All hotels its income less than 2000 has been deleted from the system");
        }
        public void delete_booking(string ID)
        {
            bool f = false;
            int tempsize = bSize;
            var bList = b.ToList();
            for (int i = 0; i < tempsize; i++)
            {
                if (b[i].getID() == ID)
                {
                    f = true;
                    int n = b[i].getNumofRooms();
                    string h = b[i].getHotelName();
                    bList.Remove(b[i]);
                    bSize--;
                    updateRooms(h, n);
                    Console.WriteLine("The booking with ID " + ID + " is canceled successfully");
                }
            }
            if (f == false)
            {
                Console.WriteLine("There is No booking in the system matches the ID you entered");
            }
            else
            {
                b = bList.ToArray();
            }
        }
        public void updateRooms(string hotelName, int n)
        {
            for (int i = 0; i < hSize; i++)
            {
                if (h[i].getName() == hotelName)
                {
                    int a = h[i].getNumofRooms() + n;
                    h[i].setNumofRooms(a);
                }
            }
        }
        public void add_Hotel(string n, string c, string l, double costB, double costAll, int rooms, double income, double discount)
        {

            for (int i = 0; i < hSize; i++)
            {
                if (h[i].getName() == n)
                {
                    Console.WriteLine("the hotel already exists in the system");
                    return;
                }
            }
            hotel H = new hotel(n, c, l, costB, costAll, rooms, income, discount);
            h[hSize] = H;

            FileStream fs2 = new FileStream("hotels.txt", FileMode.Append, FileAccess.Write);
            BinaryFormatter bf2 = new BinaryFormatter();

            bf2.Serialize(fs2, H);
            fs2.Close();

            Console.WriteLine("The hotel is added succesfully");
            Console.WriteLine();
            hSize++;
        }
        public void add_Customer(string name, string pass, int credit)
        {
            for (int i = 0; i < cSize; i++)
            {
                if (c[i].getName() == name)
                {
                    Console.WriteLine("the customer already exists in the system ");
                    return;
                }
            }
            customer C = new customer(name, pass, credit);
            c[cSize] = C;

            FileStream fs1 = new FileStream("customers.txt", FileMode.Append, FileAccess.Write);
            BinaryFormatter bf1 = new BinaryFormatter();

            bf1.Serialize(fs1, C);
            fs1.Close();

            Console.WriteLine("The customer is added succesfully");
            Console.WriteLine();
            cSize++;
        }
        public void add_booking(string id, string cn, string hn, int numOfRooms, int numOfDays, char meal, double bookingsCost)
        {

            for (int i = 0; i < bSize; i++)
            {
                if (b[i].getID() == id)
                {
                    Console.WriteLine("the booking already exists in the system ");
                    return;
                }
            }

            booking B = new booking(id, cn, hn, numOfRooms, numOfDays, meal, bookingsCost);

            b[bSize] = B;
            FileStream fsB = new FileStream("booking.txt", FileMode.Create, FileAccess.Write);
            BinaryFormatter bfB = new BinaryFormatter();

            bfB.Serialize(fsB, B);
            fsB.Close();
            bSize++;
        }

        public void display_bookings_related_to_specific_hotel(string hotel_name)
        {

        }

        public void update_hotel_info(string n)
        {
            bool f = false;
            for (int i = 0; i < hSize; i++)
            {
                if (h[i].getName() == n)
                {
                    f = true;
                    Console.WriteLine("Please enter the new number of available rooms : ");
                    string numR = Console.ReadLine();
                    int numRooms = Convert.ToInt32(numR);
                    h[i].setNumofRooms(numRooms);

                    Console.WriteLine("Please enter the new cost per day for breakfast : ");
                    string cB = Console.ReadLine();
                    double CB = Convert.ToDouble(cB);
                    h[i].setCostB(CB);

                    Console.WriteLine("Please enter the new cost per day for all meals : ");
                    string cA = Console.ReadLine();
                    double CA = Convert.ToDouble(cA);
                    h[i].setCostA(CA);

                    Console.WriteLine("Please enter the new discount : ");
                    string d = Console.ReadLine();
                    double D = Convert.ToDouble(d);
                    h[i].setDiscount(D);

                }
            }
            if (f == false)
            {
                Console.WriteLine("There is No hotel in the system match the hotel name you entered");
            }

        }
        public void view_hotels()
        {
            int i = 0;
            while (h[i] != null)
            {
                Console.Write("hotel name: " + h[i].getName());
                Console.WriteLine();
                Console.WriteLine();
                Console.Write("Classification: " + h[i].getClass());
                Console.WriteLine();
                Console.WriteLine();
                Console.Write("Location: " + h[i].getLocation());
                Console.WriteLine();
                Console.WriteLine();
                Console.Write("Daily cost per one room with breakfast : " + h[i].getCostB());
                Console.WriteLine();
                Console.WriteLine();
                Console.Write("Daily cost per one room with all meals : " + h[i].getCostAll());
                Console.WriteLine();
                Console.WriteLine();
                Console.Write("Number of available rooms : " + h[i].getNumofRooms());
                Console.WriteLine();
                Console.WriteLine();
                Console.Write("Total income : " + h[i].getIncome());
                Console.WriteLine();
                Console.WriteLine();
                Console.Write("Discount : " + h[i].getDiscount());
                Console.WriteLine();
                Console.WriteLine();
                i++;
            }
        }
        public void view_customers()
        {
            int i = 0;
            while (c[i] != null)
            {
                Console.Write("Customer Name : ");
                Console.WriteLine(c[i].getName());
                Console.WriteLine();
                Console.Write("Credit : ");
                Console.WriteLine(c[i].getCredit());
                Console.Write("Password : ");
                Console.WriteLine(c[i].getPass());
                Console.WriteLine();
                i++;
            }
        }
        public void view_bookings()
        {
            int i = 0;
            while (b[i] != null)
            {
                Console.Write("Booking ID : ");
                Console.WriteLine(b[i].getID());
                Console.WriteLine();
                Console.Write("Customer Name : ");
                Console.WriteLine(b[i].getCustomerName());
                Console.WriteLine();
                Console.Write("Hotel Name : ");
                Console.WriteLine(b[i].getHotelName());
                Console.WriteLine();
                Console.Write("Status : ");
                if (b[i].getStatus() == false)
                    Console.WriteLine("Not completed");
                else
                    Console.WriteLine("Completed");
                Console.WriteLine();
                Console.Write("Number of days : ");
                Console.WriteLine(b[i].getNumofDays());
                Console.WriteLine();
                Console.Write("Number of rooms : ");
                Console.WriteLine(b[i].getNumofRooms());
                Console.WriteLine();
                Console.Write("Meal Type : ");
                Console.WriteLine(b[i].getMealType());
                Console.WriteLine();
                Console.Write("Bookings cost : ");
                Console.WriteLine(b[i].getCost());
                Console.WriteLine();

                i++;
            }
        }
        public string getCnames(int i)
        {
            return c[i].getName();
        }
        public string GetPass(int i)
        {
            return c[i].getPass();
        }
        public double getCcredit(int i)
        {
            return c[i].getCredit();
        }
        public int get_cSize()
        {
            return cSize;
        }
        public int get_bSize()
        {
            return bSize;
        }
    }

    public class Program
    {
        public static void Main(string[] args)
        {
            customer c1 = new customer("Ali", "123", 5000);
            customer c2 = new customer("Sami", "456", 8000);
            customer c3 = new customer("Nuha", "789", 2000);
            customer c4 = new customer("Ola", "246", 15000);

            FileStream fs1 = new FileStream("customers.txt", FileMode.Create, FileAccess.Write);
            BinaryFormatter bf1 = new BinaryFormatter();

            bf1.Serialize(fs1, c1);
            bf1.Serialize(fs1, c2);
            bf1.Serialize(fs1, c3);
            bf1.Serialize(fs1, c4);

            fs1.Close();

            hotel h1 = new hotel("Dreams", "Four stars", "Irbid", 25, 40, 97, 2500, 0);
            hotel h2 = new hotel("Moon", "Five stars", "Amman", 30, 60, 35, 8000, 0.1);
            hotel h3 = new hotel("VIP", "Five stars", "Irbid", 32, 70, 13, 1200, 0.3);
            hotel h4 = new hotel("Down town", "Three stars", "Aqaba", 10, 22, 200, 1000, 0);
            hotel h5 = new hotel("Days Inn", "Five stars", "Wadi rum", 30, 75, 140, 18520, 0.2);
            hotel h6 = new hotel("Rose ", "Four stars", "Petra ", 36, 76, 86, 1560, 0.15);
            hotel h7 = new hotel("Red Sea", "Five stars", "Aqaba", 42, 98, 177, 9000, 0.25);
            hotel h8 = new hotel("Ramada", "Five stars", "Aqaba", 50, 110, 222, 15000, 0.3);

            FileStream fs2 = new FileStream("hotels.txt", FileMode.Create, FileAccess.Write);
            BinaryFormatter bf2 = new BinaryFormatter();

            bf2.Serialize(fs2, h1);
            bf2.Serialize(fs2, h2);
            bf2.Serialize(fs2, h3);
            bf2.Serialize(fs2, h4);
            bf2.Serialize(fs2, h5);
            bf2.Serialize(fs2, h6);
            bf2.Serialize(fs2, h7);
            bf2.Serialize(fs2, h8);

            fs2.Close();

            administrator admin = new administrator();
            customer c = new customer();

            string s = "1";
            while (s != "3")
            {
                Console.WriteLine("1) Login as Administrator.");
                Console.WriteLine("2) Login as Customer.");
                Console.WriteLine("3) Exit.");
                Console.WriteLine();
                Console.WriteLine("Please enter your choice : ");
                s = Console.ReadLine();
                if (s == "1")
                {
                    bool x = true;
                    while (x == true)
                    {
                        Console.WriteLine("Enter username : ");
                        string aName = Console.ReadLine();
                        Console.WriteLine("Enter password : ");
                        string aPass = Console.ReadLine();
                        if (admin.log_in(aName, aPass) == true) x = false;
                    }
                    bool y = true;
                    while (y == true)
                    {
                        Console.WriteLine();
                        Console.WriteLine("1) Add a hotel to the system.");
                        Console.WriteLine("2) Add customer to the system.");
                        Console.WriteLine("3) View all hotels.");
                        Console.WriteLine("4) View all customers.");
                        Console.WriteLine("5) View all bookings.");
                        Console.WriteLine("6) View all bookings that are related to a specific hotel.");
                        Console.WriteLine("7) Update hotel information.");
                        Console.WriteLine("8) Delete a hotel from the system.");
                        Console.WriteLine("9) Logout");
                        Console.WriteLine();
                        Console.WriteLine("Please enter your choice : ");
                        string a = Console.ReadLine();

                        if (a == "1") //add hotel to the system
                        {
                            admin.add_hotel();
                        }
                        if (a == "2") //add customer to the system
                        {
                            Console.WriteLine("Please enter customer's name : ");
                            string n = Console.ReadLine();
                            admin.add_customer(n);
                        }
                        if (a == "3") //view all hotels
                        {
                            admin.view('h');
                        }
                        if (a == "4") //view all customer
                        {
                            admin.view('c');
                        }
                        if (a == "5") //view all bookings
                        {
                            admin.view('b');
                        }
                        if (a == "6") //view all bookings related to a specific hotel
                        {
                            admin.view_all_bookings_related_to_specific_hotel("");
                        }
                        if (a == "7") //update hotel information
                        {
                            admin.update_hotel_info();
                        }
                        if (a == "8") //delete a hotel from the system
                        {
                            admin.delete_hotel();
                        }

                        if (a == "9") //log out
                        {
                            y = false;
                            continue;
                        }
                    }
                }
                else if (s == "2")
                {
                    bool w = true;
                    while (w == true)
                    {
                        Console.WriteLine("Enter username : ");
                        string cName = Console.ReadLine();
                        Console.WriteLine("Enter password : ");
                        string cPass = Console.ReadLine();
                        if (c.log_in(cName, cPass) == true)
                            w = false;
                    }
                    bool z = true;
                    while (z == true)
                    {
                        Console.WriteLine();
                        Console.WriteLine("1) Make a hotel booking.");
                        Console.WriteLine("2) View all my booking(s).");
                        Console.WriteLine("3) Cancel booking befor paying money (not completed bookings).");
                        Console.WriteLine("4) Pay for bookings.");
                        Console.WriteLine("5) Logout");
                        Console.WriteLine();
                        Console.WriteLine("Please enter your choice.");
                        string a = Console.ReadLine();
                        if (a == "1")//make hotel booking
                        {
                            Console.WriteLine("Please enter the booking ID : ");
                            string id = Console.ReadLine();
                            c.make_booking(id);
                        }
                        if (a == "2")//view all my bookins(s)
                        {
                            c.view_my_bookings();
                        }
                        if (a == "3")//Cancel booking befor paying money (not completed bookings)
                        {
                            Console.WriteLine("Please enter the booking ID to cancel it : ");
                            string id = Console.ReadLine();
                            c.cancel_booking(id);
                        }
                        if (a == "4")//Pay for bookings.
                        {
                            c.pay();
                        }
                        if (a == "5")//logout
                        {
                            z = false;
                            continue;
                        }
                    }
                }
                else if (s == "3")
                {
                    break;
                }
                else
                {
                    Console.WriteLine("Wrong choice");
                }
            }
        }
    }
}