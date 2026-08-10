#include "/home/codeleaded/System/Static/Library/WindowEngine.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"

typedef struct Gradient_Point {
    Vec2 p;
    Vec2 v;
    float rad;
    float r;
    float g;
    float b;
} Gradient_Point;


TransformedView tv;
Vector points;

void Setup(AlxWindow* w){
    tv = TransformedView_Make(
        (Vec2){ GetWidth(),GetHeight() },
        (Vec2){ 0.0f,0.0f },
        (Vec2){ 0.01f,0.01f },
        (float)GetWidth() / (float)GetHeight()
    );
    
    points = Vector_New(sizeof(Gradient_Point));
    
    Vector_Push(&points,(Gradient_Point[]){{
        .p = { 0.0f,0.0f },
        .v = { -100.0f,100.0f },
        .r = 1.0f,
        .g = 0.0f,
        .b = 0.0f,
        .rad = 5000.0f
    }});
    Vector_Push(&points,(Gradient_Point[]){{
        .p = { 100.0f,0.0f },
        .v = { -100.0f,-100.0f },
        .r = 0.0f,
        .g = 1.0f,
        .b = 0.0f,
        .rad = 5000.0f
    }});
    Vector_Push(&points,(Gradient_Point[]){{
        .p = { 0.0f,100.0f },
        .v = { 100.0f,100.0f },
        .r = 0.0f,
        .g = 0.0f,
        .b = 1.0f,
        .rad = 5000.0f
    }});
    Vector_Push(&points,(Gradient_Point[]){{
        .p = { 100.0f,100.0f },
        .v = { 100.0f,-100.0f },
        .r = 1.0f,
        .g = 1.0f,
        .b = 0.0f,
        .rad = 5000.0f
    }});
}
void Update(AlxWindow* w){
    TransformedView_HandlePanZoom(&tv,w->Strokes,GetMouse());
    const Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
    
    for(unsigned int i = 0;i<points.size;i++){
        Gradient_Point* const gp = (Gradient_Point*)Vector_Get(&points,i);
        gp->p.x += gp->v.x * w->ElapsedTime;
        gp->p.y += gp->v.y * w->ElapsedTime;

        if(gp->p.x < 0.0f || gp->p.x >= 150.0f) gp->v.x *= -1.0f;
        if(gp->p.y < 0.0f || gp->p.y >= 150.0f) gp->v.y *= -1.0f;
    }

    const Vec2 tl = TransformedView_ScreenWorldPos(&tv,(Vec2){ 0.0f,0.0f });
    const Vec2 br = TransformedView_ScreenWorldPos(&tv,(Vec2){ GetWidth(),GetHeight() });
    const Vec2 sd = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });
    
    for(float y = floorf(tl.y);y<br.y;y+=1.0f){
        for(float x = floorf(tl.x);x<br.x;x+=1.0f){
            float r = 0.5f;
            float g = 0.5f;
            float b = 0.5f;
            
            for(unsigned int i = 0;i<points.size;i++){
                Gradient_Point* const gp = (Gradient_Point*)Vector_Get(&points,i);
                
                const float dx = x - gp->p.x;
                const float dy = y - gp->p.y;
                const float l = (dx * dx + dy * dy) / gp->rad;
                
                r += gp->r / (l < 1.0f ? 1.0f : l);
                g += gp->g / (l < 1.0f ? 1.0f : l);
                b += gp->b / (l < 1.0f ? 1.0f : l);
            }
            
            r /= (float)points.size;
            g /= (float)points.size;
            b /= (float)points.size;

            const Pixel c = Pixel_toRGBA(r,g,b,1.0f);
            const Vec2 sp = TransformedView_WorldScreenPos(&tv,(Vec2){ x,y });
            Rect_RenderXX(WINDOW_STD_ARGS,sp.x,sp.y,sd.x + 1.0f,sd.y + 1.0f,c);
        }
    }
}
void Delete(AlxWindow* w){
    Vector_Free(&points);
}

int main(){
    if(Create("Gradient",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}