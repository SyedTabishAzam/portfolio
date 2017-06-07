#include "objectList.h"




objectList::objectList()
{
    head = NULL;
    tail = NULL;


}

objectList::~objectList()
{
    cout<<"objectList Destroyed"<<endl;
}

void objectList::Drawall(BITMAP* buffer)
{ //if the list isnt empty, draw every node's object
    if(!isEmpty())
    {
        Node<Shape*>* temp = head;
        temp->object->Draw(buffer);
        temp = temp->next;
        while(temp != head)
        {
            if(temp->object->alive) //this checks if whether the object is alive or not (not alive means its in the list but not has to be drawn)
                temp->object->Draw(buffer);
            temp = temp->next;
        }
    }

}



void objectList::moveup()
{   //calles the function Change Position (Cposition) of shape
    if(!isEmpty())
    {
        tail->object->CPosition(0); //passes 0 to tell if it is moving up,
    }
}

void objectList::movedown()
{
    if(!isEmpty())
    {
        tail->object->CPosition(1); //passes 0 to tell if it is moving up,
    }
}


void objectList::WriteFile()
{
    ofstream htmlFile;
    htmlFile.open ("Drawit.html");  //Name of the HTML file to be created
    htmlFile<<"<!DOCTYPE html>\n<html>\n<head>\n<title>Draw it!</title>\n</head>\n<body>\n";
    htmlFile<<"<canvas id=\"myCanvas\" width=\"800\" height=\"600\" style=\"background-color:rgb(0,0,0);\"></canvas>\n";
    htmlFile<<"<script>\n";
    htmlFile<<"var c = document.getElementById(\"myCanvas\");\n";
    htmlFile<<"var ctx = c.getContext(\"2d\");\n";
    //*********** Draw Figures Here ************

    if(isEmpty() == false)
    {
        Node<Shape*>* temp = getHead();
        int k = GetLength();

        for(int i = 0; i<k; i++)
        {

            int color_value = temp->object->GetColor();
            int r = getr(color_value);
            int g = getg(color_value);
            int b = getb(color_value);
            string type = temp->object->GetType();

            if (type=="p")
            {
                htmlFile<<"ctx.fillStyle = \"rgb("<<r<<","<<g<<","<<b<<")\";\n";

                htmlFile<<"ctx.fillRect("<<temp->object->GetPosition().x<<","<<temp->object->GetPosition().y<<",1,1);\n";
                //break;
            }
            if(type=="l")
            {

                htmlFile<<"ctx.moveTo("<<temp->object->GetPosition().x<<","<<temp->object->GetPosition().y<<");\n";
                htmlFile<<"ctx.lineTo("<<temp->object->GetBottomRight().x<<","<<temp->object->GetBottomRight().y<<");\n";
                htmlFile<<"ctx.strokeStyle = \"rgb("<<r<<","<<g<<","<<b<<")\";\n";
                htmlFile<<"ctx.stroke();\n";
                //break;
            }
            if(type=="r")
            {


                htmlFile<<"ctx.fillStyle = \"rgb("<<r<<","<<g<<","<<b<<")\";\n";

                htmlFile<<"ctx.fillRect("<<temp->object->GetLength()<<","<<temp->object->GetBreadth()<<","<<temp->object->GetPosition().x - temp->object->GetLength()<<","<<temp->object->GetPosition().y - temp->object->GetBreadth()<<");\n";
                //break;
            }
            if(type=="c")
            {


                htmlFile<<"ctx.beginPath();\n";
                htmlFile<<"ctx.arc("<<temp->object->GetPosition().x<<","<<temp->object->GetPosition().y<<","<<temp->object->GetRadius()<<",0,2*Math.PI);\n";
                htmlFile<<"ctx.fillStyle = \"rgb("<<r<<","<<g<<","<<b<<")\";\n";
                htmlFile<<"ctx.fill();\n";
                htmlFile<<"ctx.strokeStyle = \"rgb("<<r<<","<<g<<","<<b<<")\";\n";
                htmlFile<<"ctx.stroke();\n";
                //break;
            }
            temp = temp->next;
        }
    }
    //******************************************
    htmlFile<<"</script>\n</body>\n</html>";
	htmlFile.close();   //Closing the HTML file
}
