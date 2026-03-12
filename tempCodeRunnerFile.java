import java.util.*;

public class login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Map<String, String> users = new HashMap<>();
        String username = null;
        String password = null;
        




        while (true) {
            System.out.println("1. log in\n2. sign up\n0. exit");
            System.out.print("Choose option: ");
            int a = sc.nextInt();

            switch (a) {
                case 1:
                    System.out.print("Enter username: ");
                    username = sc.next();
                    System.out.print("Enter password: ");
                    password = sc.next();
                    if (users.containsKey(username) && users.get(username).equals(password)) {
                        System.out.println("Hello " + username + ", welcome back");
                    } else {
                        System.out.println("Incorrect username and password pair");
                    }
                    break;
                case 2:
                    System.out.print("Enter username: ");
                    username = sc.next();
                    boolean passwordsMatch = false;
                    do {
                        System.out.print("Enter password: ");
                        password = sc.next();
                        System.out.print("Reenter password: ");
                        String password_re = sc.next();
                        if (password.equals(password_re)) {
                            passwordsMatch = true;
                            users.put(username, password);
                            System.out.println("Your account has been created");
                        } else {
                            System.out.println("Passwords don't match. Try again.");
                        }
                    } while (!passwordsMatch);
                    break;
                case 0:
                    sc.close();
                    System.exit(0);
                    break;
                default:
                    System.out.println("Wrong input");
            }
        }
    }
}