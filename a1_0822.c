#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SENTENCES 30
#define MAX_LINE_LEN 100

char *a_nums[] = {"A01329221", "A01350858", "A01329554"};
int maxLength(const char *str)
{
    int max_len = 0, curr_len = 0;
    while (*str)
    {
        if (*str != ' ')
        {
            curr_len++;
        }
        else
        {
            if (curr_len > max_len)
                max_len = curr_len;
            curr_len = 0;
        }
        str++;
    }
    if (curr_len > max_len)
        max_len = curr_len;
    return max_len;
}

void trimLine(char *str)
{
    int len = strlen(str);
    int trailing_spaces = 0;

    // Count the trailing spaces
    for (int i = len - 1; i >= 0 && str[i] == ' '; i--)
    {
        trailing_spaces++;
    }

    // Trim the trailing spaces
    str[len - trailing_spaces] = '\0';
}

void printLine(const char *str, int total_len)
{

    int len = strlen(str);
    int gap_count = 0, i;

    for (i = 0; i < len; i++)
    {
        if (str[i] == ' ')
            gap_count++;
    }

    int needed_spaces = total_len - len;
    int space_per_gap = (gap_count == 0) ? 0 : needed_spaces / gap_count;
    int additional_spaces = (gap_count == 0) ? 0 : needed_spaces % gap_count;

    if (gap_count == 0)
    {
        // Center a single word by adding spaces both before and after the word
        int leading_spaces = (needed_spaces / 2);
        int trailing_spaces = needed_spaces - leading_spaces;
        for (int s = 0; s < leading_spaces; s++)
            putchar(' ');
        for (i = 0; i < len; i++)
        {
            putchar(str[i]);
        }
        for (int s = 0; s < trailing_spaces; s++)
            putchar(' ');
    }
    else
    {
        for (i = 0; i < len; i++)
        {
            putchar(str[i]);
            if (str[i] == ' ')
            {
                for (int s = 0; s < space_per_gap; s++)
                    putchar(' ');
                if (additional_spaces)
                {
                    putchar(' ');
                    additional_spaces--;
                }
            }
        }
    }
    putchar('\n');
}

void justifyText(char **lines, int count, int line_len)
{

    for (int i = 0; i < count; i++)
    {
        char *current = lines[i];

        while (strlen(current) > 0)
        {
            char temp[MAX_LINE_LEN];

            if (strlen(current) <= line_len)
            {
                strcpy(temp, current);
                printLine(temp, line_len);
                break;
            }

            int cut_at = line_len;

            for (int j = cut_at; j >= 0; j--)
            {
                if (current[j] == ' ' || current[j] == '-')
                {
                    if (current[j] == '-')
                    {
                        // Cut just before the hyphen
                        cut_at = j + 1;
                    }
                    else
                    {
                        cut_at = j + 1; // Include the space
                    }
                    break;
                }
            }

            strncpy(temp, current, cut_at);
            temp[cut_at] = '\0';

            // Trim the line before processing
            trimLine(temp);
            // printf("current: %s", temp);
            // printf("anything\n");

            printLine(temp, line_len);
            current += cut_at;
            while (*current == ' ')
            {
                current++;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <line_length> <filename>\n", argv[0]);
        return 1;
    }

    int line_len = atoi(argv[1]);
    char *filename = argv[2];

    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("Unable to open file");
        return 1;
    }

    char buffer[MAX_LINE_LEN];
    char *lines[MAX_SENTENCES];
    int num_lines = 0;

    while (fgets(buffer, sizeof(buffer), fp) && num_lines < MAX_SENTENCES)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        lines[num_lines] = strdup(buffer);
        num_lines++;
    }

    fclose(fp);

    for (int i = 0; i < num_lines; i++)
    {
        int max_word_length = maxLength(lines[i]);
        if (max_word_length > line_len)
        {
            printf("Error. The word processor can't display the output.\n");
            for (int j = 0; j < num_lines; j++)
                free(lines[j]);
            return 0;
        }
    }

    justifyText(lines, num_lines, line_len);

    // Create an output file with the name stored in ANum
    for (int i = 0; i < 3; i++)
    {
        FILE *outputFile = fopen(a_nums[i], "w");
        // Check if the output file was created successfully
        if (outputFile == NULL)
        {
            printf("Failed to create the output file.\n");
            return 1;
        }
    }

    for (int i = 0; i < num_lines; i++)
        free(lines[i]);

    return 0;
}
