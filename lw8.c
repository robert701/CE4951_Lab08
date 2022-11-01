#include <stdio.h>
#include <string.h>
#include <unistd.h>


// The variables for the inputs of the IP header
unsigned int Version = 4;
unsigned int IHL;
unsigned int DSCP;
unsigned int ECN;
unsigned int Total_Length;
unsigned int ID;
unsigned int Flags;
unsigned int Frag_Offset;
unsigned int TTL;
unsigned int Protcol;

// The initial checksum of 0 for our calculation
unsigned int default_checksum = 0;

// The source IP values, for inputting and parsing the source IP
char source_IP[17];
unsigned int source_IP1;
unsigned int source_IP2;

// The destination IP values, for inputting and parsing the destination IP
char Destination_IP[17];
unsigned int destination_IP1;
unsigned int destination_IP2;

// IP numbers, for parsing the dotted quads
unsigned int IP1;
unsigned int IP2;
unsigned int IP3;
unsigned int IP4;

// Options
unsigned int options_Total = 0;
unsigned int option_Input1;
unsigned int option_Input2;

unsigned int Option1 = 0;
unsigned int Option2 = 0;
unsigned int Option3 = 0;
unsigned int Option4 = 0;


// Sums to be returned from funcitons
unsigned int baseSum = 0;
unsigned int IPSum = 0;

// The calculated checksum to be calculated
unsigned int Calculated_Checksum = 0;

// The cary value for the sum
unsigned int carry;

// This is the max value that a 16 bit number can reach, FFFF
unsigned int MAX = 0xFFFF;
unsigned int OverFlow = 0x10000;

// The function that asks the user for the base and sums the values
unsigned int addBaseIPV4();

// The function that asks for and adds options if applicable
unsigned int addOptions();

// The funciton that asks for the IP address in dotted quads,
// parses them, and sums them
unsigned int IP_input();

// Function that prints out the IP header in a formatted output
void IP_output();

// Function that prints the options at the end of the IP header
void Options_output();

int main()
{

    Calculated_Checksum += addBaseIPV4();
    Calculated_Checksum += IP_input();

    if (IHL > 5)
    {
        Calculated_Checksum += addOptions();
    }

    // Carry calculation
    if (Calculated_Checksum >= OverFlow)
    {
        // I think this is where I am going wrong
        // My math seems off
        carry = Calculated_Checksum - MAX;
        Calculated_Checksum -= MAX;
        Calculated_Checksum += carry;
    }
    printf("--------------------------------------------------\n");

    printf("Your total checksum is: %X \n", Calculated_Checksum);
    Calculated_Checksum = ~Calculated_Checksum;

    printf("Your inverted checksum is: %X \n", Calculated_Checksum);
    printf("--------------------------------------------------\n");
    printf("\n");

    return 0;
}

unsigned int addOptions()
{
    printf("--------------------------------------------------\n");

    printf("you entered %i for IHL, meaning you have %i options", IHL, (9 - IHL));
    printf("--------------------------------------------------\n");
    printf("\n");

    for (int i = 0; i < (9 - IHL); i++)
    {
        printf("--------------------------------------------------\n");
        printf("Please enter the first half of option number  %i \n", i);
        scanf("%X", &option_Input1);
        printf("You entered %X \n", option_Input1);
        printf("Please enter the second half of option number %i \n", i);
        scanf("%X", &option_Input2);
        printf("You entered %X \n", option_Input2);
        options_Total += ((option_Input1 << 8) + option_Input2);
        if(i =6){
            Option1 = ((option_Input1<<8) + option_Input2);

        }else if(i == 7){
             Option2 = ((option_Input1<<8) + option_Input2);

        }else if(i == 8){
             Option3 = ((option_Input1<<8) + option_Input2);
            
        } else if(i==9){
             Option4 = ((option_Input1<<8) + option_Input2);

        }

        printf("--------------------------------------------------\n");
    }

    printf("--------------------------------------------------\n");
    printf("Your total options: %X \n", options_Total);
    printf("--------------------------------------------------\n");
    printf("\n");

    return options_Total;
}

unsigned int addBaseIPV4()
{
    printf("--------------------------------------------------\n");
    printf("This program will request numbers for an IPV4 header from you the user, and calculate the checksum. \n");
    printf("Then it formats the IP header and prints it out \n");
    printf("--------------------------------------------------\n");

    printf("\n");

    printf("--------------------------------------------------\n");
    printf("This used IPV4, so the version number is set to 4 \n");
    printf("--------------------------------------------------\n");
    baseSum += Version;
    printf("\n");

    printf("--------------------------------------------------\n");
    printf("Please enter the IHL. Note is has has a minimum length of 5 and a maximum of 9 \n");
    printf("If you enter a value less than 5 it will be set to 5, or if greater than 9 it will be set to 9. \n");
    printf("Please use hex, but the 0x prefix is not needed if you don't want to \n");
    // fgets(input, 250, stdin);
    scanf("%X", &IHL);

    if (IHL < 5)
    {
        IHL = 5;
    }
    else if (IHL > 9)
    {
        IHL = 9;
    }
    printf(" IHL being used: %X\n", IHL);

    printf("--------------------------------------------------\n");
    printf("\n");
    baseSum += IHL;

    printf("--------------------------------------------------\n");
    printf("Please enter the DSCP value, in hex again \n");
    scanf("%X", &DSCP);
    printf("You entered: %X \n", DSCP);
    printf("--------------------------------------------------\n");
    printf("\n");
    baseSum += DSCP;

    printf("--------------------------------------------------\n");
    printf("Please enter ECN, which has a max of 3, in hex again \n");
    scanf("%X", &ECN);
    if (ECN > 3)
    {
        ECN = 3;
    }
    printf("You entered: %X \n", ECN);
    printf("--------------------------------------------------\n");
    printf("\n");
    baseSum += ECN;

    printf("--------------------------------------------------\n");
    printf("Please enter the Total Length, in hex again \n");
    scanf("%X", &Total_Length);
    printf("You entered: %X \n", Total_Length);
    printf("--------------------------------------------------\n");
    printf("\n");
    baseSum += Total_Length;

    printf("--------------------------------------------------\n");
    printf("Please enter the Identification, in hex again \n");
    scanf("%X", &ID);
    printf("You entered: %X \n", ID);
    printf("--------------------------------------------------\n");
    printf("\n");
    baseSum += ID;

    printf("--------------------------------------------------\n");
    printf("Please enter the Flags, which have a max of 7, in hex again \n");
    scanf("%X", &Flags);
    if (Flags > 7)
    {
        Flags = 7;
    }
    printf("You entered: %X \n", Flags);
    printf("--------------------------------------------------\n");
    printf("\n");
    baseSum += Flags;

    printf("--------------------------------------------------\n");
    printf("Please enter the Fragment Offset, in hex again \n");
    scanf("%X", &Frag_Offset);
    printf("You entered: %X \n", Frag_Offset);
    printf("--------------------------------------------------\n");
    printf("\n");
    baseSum += Frag_Offset;

    printf("--------------------------------------------------\n");
    printf("Please enter the Time to Live, in hex again \n");
    scanf("%X", &TTL);
    printf("You entered: %X \n", TTL);
    printf("--------------------------------------------------\n");
    printf("\n");
    baseSum += TTL;

    printf("--------------------------------------------------\n");
    printf("Please enter the Protocol, in hex again \n");
    scanf("%X", &Protcol);
    printf("You entered: %X \n", Protcol);
    printf("--------------------------------------------------\n");
    printf("\n");
    baseSum += Protcol;

    printf("the header checksum is 0 because we are calculating it, you do not need to enter it \n");
    baseSum += default_checksum;

    return baseSum;
}

unsigned int IP_input()
{
    printf("--------------------------------------------------\n");
    printf("Please enter the source IP address, in quad decimal spaced format: 192.158.1.38 \n");
    scanf("%s", source_IP);
    printf("You entered: %s \n", source_IP);
    printf("--------------------------------------------------\n");
    printf("\n");

    sscanf(source_IP, "%u.%u.%u.%u", &IP1, &IP2, &IP3, &IP4);

    IP1 = IP1 << 8;
    source_IP1 = IP1 + IP2;
    IP3 = IP3 << 8;
    source_IP2 = IP3 + IP4;

    printf("--------------------------------------------------\n");
    printf("Please enter the destination IP address, in quad decimal spaced format: 192.158.1.38 \n");
    scanf("%s", Destination_IP);
    printf("You entered: %s \n", Destination_IP);
    printf("--------------------------------------------------\n");
    printf("\n");

    sscanf(source_IP, "%u.%u.%u.%u", &IP1, &IP2, &IP3, &IP4);

    IP1 = IP1 << 8;
    destination_IP1 = IP1 + IP2;
    IP3 = IP3 << 8;
    destination_IP2 = IP3 + IP4;

    IPSum = source_IP1 + source_IP2 + destination_IP1 + destination_IP2;

    return IPSum;
}

void IP_output()
{
    printf("--------------------------------------------------\n");
    printf("IP Header: \n");

    printf("%X%X%X%X%X \n", Version, IHL, DSCP, ECN, Total_Length);
    printf("%X%X%X \n", ID, Flags, Frag_Offset);
    printf("%X%X%X \n", TTL, Protcol, Calculated_Checksum);
    printf("%X%X \n", source_IP1, source_IP2);
    printf("%X%X \n", destination_IP1, destination_IP2);

    if(IHL>5)
    {
        Options_output();
    }

    printf("--------------------------------------------------\n");
}

void Options_output()
{
    if(Option1 != 0){
        printf("%X \n", Option1);
    }

    if(Option2 != 0){
        printf("%X \n", Option2);
    }

    if(Option3 != 0){
        printf("%X \n", Option3);
    }

    if(Option4 != 0){
        printf("%X \n", Option4);
    }

}