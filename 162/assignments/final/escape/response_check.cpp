#include "response_check.h"

/******************************************************************************
* Entry: 2 char values for which the function can check against
*
* Exit: gets user input and compares it to the valid responses until it finally
*       gets a valid response
*
* Purpose: checking that a response is valid
*
******************************************************************************/
char responseCheck(char val1, char val2)
{
    char response = '\0'; //user input

    //checks user input against given valid characters
    while(response != val1 && response != val2)
    {
        //print options
        cout << "Please enter only: " << val1
             << " or " << val2
             << endl;

        cin.get(response);

        if(response != '\n')
        {
            cin.ignore(INT_MAX, '\n');
        }

        if(isalpha(response))
            response = toupper(response);
    }

    cout << endl;

    return response;
}

/******************************************************************************
* Entry: 3 char values for which the function can check against
*
* Exit: gets user input and compares it to the valid responses until it finally
*       gets a valid response
*
* Purpose: checking that a response is valid
*
******************************************************************************/
char responseCheck(char val1, char val2, char val3)
{
    char response = '\0'; //user input

    //checks user input against given valid characters
    while(response != val1
          && response != val2
          && response != val3)
    {
        //print options
        cout << "Please enter only: " << val1
             << " or " << val2
             << " or " << val3
             << endl;

        cin.get(response);

        if(response != '\n')
        {
            cin.ignore(INT_MAX, '\n');
        }

        if(isalpha(response))
            response = toupper(response);
    }

    cout << endl;

    return response;
}

/******************************************************************************
* Entry: 4 char values for which the function can check against
*
* Exit: gets user input and compares it to the valid responses until it finally
*       gets a valid response
*
* Purpose: checking that a response is valid
*
******************************************************************************/
char responseCheck(char val1, char val2, char val3, char val4)
{
    char response = '\0'; //user input

    //checks user input against given valid characters
    while(response != val1
          && response != val2
          && response != val3
          && response != val4)
    {
        //print options
        cout << "Please enter only: " << val1
             << " or " << val2
             << " or " << val3
             << " or " << val4
             << endl;

        cin.get(response);

        if(response != '\n')
        {
            cin.ignore(INT_MAX, '\n');
        }

        if(isalpha(response))
            response = toupper(response);
    }

    cout << endl;

    return response;
}

/******************************************************************************
* Entry: 5 char values for which the function can check against
*
* Exit: gets user input and compares it to the valid responses until it finally
*       gets a valid response
*
* Purpose: checking that a response is valid
*
******************************************************************************/
char responseCheck(char val1, char val2, char val3, char val4, char val5)
{
    char response = '\0'; //user input

    //checks user input against given valid characters
    while(response != val1
          && response != val2
          && response != val3
          && response != val4
          && response != val5)
    {
        //print options
        cout << "Please enter only: " << val1
             << " or " << val2
             << " or " << val3
             << " or " << val4
             << " or " << val5
             << endl;

        cin.get(response);

        if(response != '\n')
        {
            cin.ignore(INT_MAX, '\n');
        }

        if(isalpha(response))
            response = toupper(response);
    }

    cout << endl;

    return response;
}
