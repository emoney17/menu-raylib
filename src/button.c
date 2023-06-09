#include "button.h"
#include "screens.h"

Vector2 mousePoint = {0, 0};

Button *createButton(const char* title, const char* texturePath, const char *soundPath, float x, float y)
{
    Button *button = malloc(sizeof(Button));

    button->title = title;
    button->texture = LoadTexture(texturePath);
    button->sound = LoadSound(soundPath);
    button->posX = x;
    button->posY = y;

    button->frameHeight = (float)button->texture.height / 2;

    button->source.x = 0;
    button->source.y = 0;
    button->source.width = (float)button->texture.width;
    button->source.height = button->frameHeight;

    button->bounds.x = button->posX;
    button->bounds.y = button->posY;
    button->bounds.width = (float)button->texture.width;
    button->bounds.height = (float)button->texture.height / 2;

    // Commenting this cause graphical errors, upate text initially and every frame
    if (button->title != NULL) {
        int textWidth = MeasureText(button->title, 12);
        button->textX = ((float)button->texture.width - textWidth) / 2.0f + button->posX;
        button->textY = button->posY + 10.0f;
    }

    return button;
}

void updateButton(Button *button)
{
    SetSoundVolume(button->sound, volume);
    mousePoint = GetMousePosition();
    button->action = false;

    // update button title positions
    if (button->title != NULL) {
        int textWidth = MeasureText(button->title, 12);
        button->textX = ((float)button->texture.width - textWidth) / 2.0f + button->posX;
        button->textY = button->posY + 10.0f;
    }

    //clicking buttons
    if (CheckCollisionPointRec(mousePoint, button->bounds)) {

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            button->state = PRESSED;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            button->action = true;
            button->state = DEFAULT;
        }
    }
    else {
        button->state = DEFAULT;
    }

    // Move to function it is called in
    //do button actions here
    // if (button->action) {
    //     printf("Button pressed. Audio should play here.\n");
    //     PlaySound(button->sound);
    // }

    button->source.y = button->state * button->frameHeight;
}

void drawButton(Button *button)
{
    DrawTextureRec(button->texture, button->source, (Vector2){button->posX, button->posY}, WHITE);
    DrawText(button->title, button->textX, button->textY, 12, BLACK);
}

void unloadButton(Button *button)
{
    UnloadTexture(button->texture); 
    UnloadSound(button->sound);

    if(button != NULL) {
        printf("BUTTON: %s ", button->title);
        free(button);
        button = NULL;
        printf("freed\n");
    }
    else {
        printf("ERROR: Could not free button %s\n", button->title);
    }
}
