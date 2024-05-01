/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** APrimitive
*/

#pragma once

    #include "IPrimitive.hpp"

class APrimitive : public IPrimitive {
    public:
        APrimitive();
        APrimitive(shared_ptr<IMaterial> _mat);
        APrimitive(const APrimitive &obj);
        ~APrimitive();
    public:
        shared_ptr<IMaterial> getMat() const;
        void setMat(shared_ptr<IMaterial> _mat);
        virtual bool hit(const Ray &ray, Interval ray_t, HitRecord &rec) const override = 0;
    public:
        APrimitive &operator=(const APrimitive &obj);
    public:
        class PrimError : public std::exception {
            public:
                PrimError(std::string msg) : _msg(msg) {};
                ~PrimError() {};
            private:
                const char *what() const noexcept override {return _msg.c_str();};
            private:
                std::string _msg;
        };
    private:
        shared_ptr<IMaterial> mat;
};
