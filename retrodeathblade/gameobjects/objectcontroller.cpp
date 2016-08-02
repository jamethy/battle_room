#include "gameobjects/objectcontroller.h"
#include "SDL_rect.h"

ObjectController::ObjectController(){

}

ObjectController::~ObjectController(){

}

void ObjectController::step_time(){
    std::vector<ObjectBaseClass*>::iterator object;
    for (object = objects.begin(); object != objects.end(); ++object)
        (*object)->step_time();

    check_for_collisions();
}

void ObjectController::drawon(SDL_Renderer *renderer, CameraControl *camera)
{
    std::vector<ObjectBaseClass*>::iterator obj;
    for(obj = objects.begin(); obj != objects.end(); ++obj){
        (*obj)->drawon(renderer,camera);
    }
}

void ObjectController::check_for_collisions(){
    std::vector<ObjectBaseClass*>::iterator object1, object2;
    for (object1 = objects.begin(); object1 != objects.end(); ++object1){
        for (object2 = object1+1; object2 != objects.end(); ++object2){

            // If neither is moving, continue
            if (!(*object1)->isMobile() && !(*object2)->isMobile()) continue;

            ObjectBaseClass* a = *object1;
            ObjectBaseClass* b = *object2;

            // Calculate if possible collision <---- should replace with quadtree
//            double dx = a->x - b->x;
//            double dy = a->y - b->y;
//            double square_dist = dx*dx + dy*dy;
//            if(square_dist > a->square_r + b->square_r) continue;

			// Some how save last axis with no overlap (returned through mtv)
			// and check before full colliding function.

            // Separate Axis Theorem
            vec2d mtv; // return object
            double mtv_mag; // return object
            if(!colliding(a,b,mtv,mtv_mag)) continue;

            //react
            bounce_objects(a,b,mtv,mtv_mag);
        }
    }
}

bool ObjectController::colliding(ObjectBaseClass* a, ObjectBaseClass* b, vec2d& return_normal, double& overlap){

    overlap = 10e10;
    std::vector<vec2d>::iterator axis;
    for(axis = a->side_normals.begin(); axis != a->side_normals.end(); ++axis){
        vec2d minmaxa = a->project_onto(*axis);
        vec2d minmaxb = b->project_onto(*axis);

        // if no overlap
        if (minmaxa[0] >= minmaxb[1] || minmaxb[0] >= minmaxa[1]){
            return false;
        }
        else{
            double newoverlap = (minmaxa[1] > minmaxb[1]) ? minmaxb[1]-minmaxa[0] : minmaxa[1]-minmaxb[0];
            if(newoverlap < overlap){
                overlap = newoverlap;
                return_normal = *axis;
            }
        }
    }

    for(axis = b->side_normals.begin(); axis != b->side_normals.end(); ++axis){
        vec2d minmaxa = a->project_onto(*axis);
        vec2d minmaxb = b->project_onto(*axis);

        // if no overlap
        if (minmaxa[0] >= minmaxb[1] || minmaxb[0] >= minmaxa[1]){
            return false;
        }
        else{
            double newoverlap = (minmaxa[1] > minmaxb[1]) ? minmaxb[1]-minmaxa[0] : minmaxa[1]-minmaxb[0];
            if(newoverlap < overlap){
                overlap = newoverlap;
                return_normal = *axis;
            }
        }
    }
    return true;
}

void ObjectController::bounce_objects(ObjectBaseClass* a, ObjectBaseClass* b, vec2d mtv_unit, double mtv_mag){

    double elasticity = a->elasticity*b->elasticity;
    double friction = a->friction*b->elasticity;

    if(a->isPlayer()){
        Player* player = (Player*)a;
        player->rebound();
    }
    if(b->isPlayer()){
        Player* player = (Player*)b;
        player->rebound();
    }

    // Situation 1: Both objects are not players, but mobile
    if( a->isMobile() && b->isMobile() ){
        vec2d cg_diff(a->x - b->x, a->y - b->y);
        vec2d mtv = mtv_unit*mtv_mag;

        //check if correct normal (parallel confusion)
        if(cg_diff.dot(mtv) < 0) mtv = mtv*-1;

        double vdotmtv = (a->dx-b->dx)*mtv_unit.x + (a->dy-b->dy)*mtv_unit.y;

        // first, uncollide
        b->translate(-(a->mass/(a->mass+b->mass))*mtv.x/2,-(a->mass/(a->mass+b->mass))*mtv.y/2);
        a->translate((b->mass/(a->mass+b->mass))*mtv.x/2,(b->mass/(a->mass+b->mass))*mtv.y/2);

        // bounce
        a->dx = friction*a->dx - (b->mass/(a->mass+b->mass))*(friction+elasticity)*vdotmtv*mtv_unit.x;
        a->dy = friction*a->dy - (b->mass/(a->mass+b->mass))*(friction+elasticity)*vdotmtv*mtv_unit.y;

        b->dx = friction*b->dx + (a->mass/(a->mass+b->mass))*(friction+elasticity)*vdotmtv*mtv_unit.x;
        b->dy = friction*b->dy + (a->mass/(a->mass+b->mass))*(friction+elasticity)*vdotmtv*mtv_unit.y;
    }


    else{
        ObjectBaseClass* mobile = (a->isMobile()) ? a : b;
        ObjectBaseClass* nonmobile = (a->isMobile()) ? b : a;

        vec2d cg_diff(mobile->x - nonmobile->x, mobile->y - nonmobile->y);
        vec2d mtv = mtv_unit*mtv_mag;

        //check if correct normal (parallel confusion)
        if(cg_diff.dot(mtv) < 0) mtv = mtv*-1;
        double vdotmtv = mobile->dx*mtv_unit.x + mobile->dy*mtv_unit.y;

        // first, uncollide
        mobile->translate(mtv.x,mtv.y);
        mobile->dx = friction*mobile->dx - (friction+elasticity)*vdotmtv*mtv_unit.x;
        mobile->dy = friction*mobile->dy - (friction+elasticity)*vdotmtv*mtv_unit.y;
    }
}


void ObjectController::add_object(ObjectBaseClass *newobject){

    for (unsigned int i = 0; i < objects.size(); ++i){
        if (newobject == objects[i]) return;
    }

    objects.push_back(newobject);
}
