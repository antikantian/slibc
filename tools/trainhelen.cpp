#include <dlib/image_processing.h>
#include <dlib/data_io.h>
#include <iostream>

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------

std::vector<std::vector<double> > get_interocular_distances (
        const std::vector<std::vector<full_object_detection> >& objects
);

int main(int argc, char** argv)
{
    try
    {
        if (argc != 2)
        {
            cout << "Give the path to the the images directory as the argument to this" << endl;
            cout << "program.  For example, if the directory is in this folder, then execute " << endl;
            cout << "this program by running: " << endl;
            cout << "   ./trainshape faces" << endl;
            cout << endl;
            return 0;
        }
        const std::string faces_directory = argv[1];

        dlib::array<array2d<unsigned char> > images_train, images_test;
        std::vector<std::vector<full_object_detection> > faces_train, faces_test;

        std::string annotations;

        cout << "Path to annotation files: ";
        cin >> annotations;



        load_image_dataset(images_train, faces_train, faces_directory + trainData);
        load_image_dataset(images_test, faces_test, faces_directory + testData);

        shape_predictor_trainer trainer;

        trainer.set_oversampling_amount(300);
        trainer.set_nu(0.05);
        trainer.set_tree_depth(2);
        trainer.be_verbose();

        shape_predictor sp = trainer.train(images_train, faces_train);

        cout << "mean training error: "<<
        test_shape_predictor(sp, images_train, faces_train, get_interocular_distances(faces_train)) << endl;

        cout << "mean testing error:  "<<
        test_shape_predictor(sp, images_test, faces_test, get_interocular_distances(faces_test)) << endl;

        std::string outdir;
        cout << "Save to file (full/path/xx.dat): ";
        cin >> outdir;

        serialize(outdir) << sp;
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}

// ----------------------------------------------------------------------------------------

double interocular_distance (
        const full_object_detection& det
)
{
    dlib::vector<double,2> l, r;
    double cnt = 0;

    for (unsigned long i = 36; i <= 41; ++i)
    {
        l += det.part(i);
        ++cnt;
    }
    l /= cnt;

    cnt = 0;
    for (unsigned long i = 42; i <= 47; ++i)
    {
        r += det.part(i);
        ++cnt;
    }
    r /= cnt;

    return length(l-r);
}

std::vector<std::vector<double> > get_interocular_distances (
        const std::vector<std::vector<full_object_detection> >& objects
)
{
    std::vector<std::vector<double> > temp(objects.size());
    for (unsigned long i = 0; i < objects.size(); ++i)
    {
        for (unsigned long j = 0; j < objects[i].size(); ++j)
        {
            temp[i].push_back(interocular_distance(objects[i][j]));
        }
    }
    return temp;
}