#include "pong.h"

// Player 1 and Player 2 paddle positions
uint16 pad_pos_y1 = 2; // Player 1
uint16 pad_pos_y2 = 2; // Player 2
uint32 score_count1 = 0; // Player 1 score
uint32 score_count2 = 0; // Player 2 score

// Initialize game with intro
static void init_game()
{
    uint8 b = 0;

    draw_string(120, 13, BRIGHT_CYAN, "PONG GAME");
    draw_rect(100, 4, 120, 25, BLUE);
    draw_string(10, 50, BRIGHT_MAGENTA, "HOW TO PLAY");
    draw_rect(2, 40, 235, 80, BROWN);
    draw_string(10, 70, BRIGHT_RED, "PLAYER 1 (ARROWS)");
    draw_string(30, 80, WHITE, "UP: ARROW UP | DOWN: ARROW DOWN");
    draw_string(10, 90, BRIGHT_RED, "PLAYER 2 (WS)");
    draw_string(30, 100, WHITE, "UP: W | DOWN: S");
    draw_string(60, 160, BRIGHT_GREEN, "PRESS ENTER TO START");
#ifdef VIRTUALBOX
    sleep(10);
#endif
    while (1)
    {
        b = get_input_keycode();
        sleep(5);
        if (b == KEY_ENTER)
            break;
        b = 0;
    }
    clear_screen();
}

// Update scores on the screen
static void update_scores()
{
    char str1[16], str2[16];
    itoa(score_count1, str1);
    itoa(score_count2, str2);

    draw_string(50, 2, WHITE, "P1: ");
    draw_string(80, 2, WHITE, str1);
    draw_string(200, 2, WHITE, "P2: ");
    draw_string(230, 2, WHITE, str2);
}

// Handle losing condition and restart game
static void lose(uint8 player)
{
    uint8 b = 0;
    clear_screen();

    if (player == 1)
    {
        draw_string(120, 15, BRIGHT_GREEN, "PLAYER 2 WINS!");
    }
    else
    {
        draw_string(120, 15, BRIGHT_GREEN, "PLAYER 1 WINS!");
    }

    draw_string(60, 160, YELLOW, "PRESS ENTER TO RESTART");

#ifdef VIRTUALBOX
    sleep(10);
#endif
    while (1)
    {
        b = get_input_keycode();
        sleep(5);
        if (b == KEY_ENTER)
            break;
        b = 0;
    }

    score_count1 = 0;
    score_count2 = 0;
    clear_screen();
    pong_game();
}

// Move paddles based on player input
void move_paddles()
{
    uint8 b;

    // Draw paddles
    fill_rect(0, pad_pos_y1, PAD_WIDTH, PAD_HEIGHT, YELLOW);           // Player 1
    fill_rect(PAD_POS_X, pad_pos_y2, PAD_WIDTH, PAD_HEIGHT, CYAN);    // Player 2

    b = get_input_keycode();
    // Player 1 controls (Arrow keys)
    if (b == KEY_DOWN && pad_pos_y1 < VGA_MAX_HEIGHT - PAD_HEIGHT)
    {
        pad_pos_y1 += PAD_SPEED;
    }
    else if (b == KEY_UP && pad_pos_y1 >= PAD_WIDTH)
    {
        pad_pos_y1 -= PAD_SPEED;
    }

    // Player 2 controls (W/S keys)
    if (b == KEY_S && pad_pos_y2 < VGA_MAX_HEIGHT - PAD_HEIGHT)
    {
        pad_pos_y2 += PAD_SPEED;
    }
    else if (b == KEY_W && pad_pos_y2 >= PAD_WIDTH)
    {
        pad_pos_y2 -= PAD_SPEED;
    }
}

void pong_game()
{
    uint16 rect_pos_x = RECT_SIZE + 20;
    uint16 rect_pos_y = RECT_SIZE;
    uint16 rect_speed_x = RECT_SPEED_X;
    uint16 rect_speed_y = RECT_SPEED_Y;

    init_game();

    while (1)
    {
        // Update ball position
        rect_pos_x += rect_speed_x;
        rect_pos_y += rect_speed_y;

        // Collision with Player 1's paddle
        if (rect_pos_x - RECT_SIZE <= PAD_WIDTH + 1)
        {
            if (rect_pos_y < pad_pos_y1 || rect_pos_y > pad_pos_y1 + PAD_HEIGHT)
            {
                lose(2); // Player 2 wins
            }
            else
            {
                rect_speed_x = -rect_speed_x;
                rect_pos_x = PAD_WIDTH + RECT_SIZE;
                score_count1++;
            }
        }
        // Collision with Player 2's paddle
        else if (rect_pos_x + RECT_SIZE >= PAD_POS_X + RECT_SIZE - 1)
        {
            if (rect_pos_y < pad_pos_y2 || rect_pos_y > pad_pos_y2 + PAD_HEIGHT)
            {
                lose(1); // Player 1 wins
            }
            else
            {
                rect_speed_x = -rect_speed_x;
                rect_pos_x = PAD_POS_X - RECT_SIZE;
                score_count2++;
            }
        }

        // Collision with screen bounds (top/bottom)
        if (rect_pos_y - RECT_SIZE <= 0 || rect_pos_y + RECT_SIZE >= VGA_MAX_HEIGHT)
        {
            rect_speed_y = -rect_speed_y;
        }

        // Clear and redraw game elements
        clear_screen();
        move_paddles();
        update_scores();
        fill_rect(rect_pos_x - RECT_SIZE, rect_pos_y - RECT_SIZE, RECT_SIZE, RECT_SIZE, WHITE);
        sleep(1);
    }
}
