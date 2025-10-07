#pragma once

#include "S101.h"

#include <pugixml.hpp>

class S101GML{
    public:
    
        static void ExportToGML(const libS101::S101 &s101cell, const libS101::String gmlPath);    

    private:
        S101GML(const libS101::S101 &s101cell);

    private:
        const libS101::S101 &cell;
        MBR invMBR; // inversed MBR
        std::unordered_map<std::string, pugi::xml_node*> objectPugiXmlElementMap;

        void SetInformationsType(pugi::xml_document* doc, pugi::xml_node parentNode, std::string productNamespace);
		void GmlifileMakeByPugi(libS101::String _filePath);
		void SetFeaturesType(pugi::xml_document* document, pugi::xml_node parentNode, std::string productNamespace);
		void SetVector(pugi::xml_node parentNode, R_FeatureRecord* fr);
		void SetVectorPointsType(pugi::xml_node parentNode, SPoint* p);
		void SetVectorMultiPointsType(pugi::xml_node parentNode, SMultiPoint* p);
		void SetVectorCurvesType(pugi::xml_node parentNode, SCurve* p);
		void SetVectorCompositeCurvesType(pugi::xml_node parentNode, SCompositeCurve* p);
		void SetVectorSurfacesType(pugi::xml_node parentNode, SSurface* p);
		void SetFeaturesTypeRelation_v2(pugi::xml_node rootNode);
		void SetInformationsTypeRelation_v2(pugi::xml_node parentNode);
		void SetAttributeType(pugi::xml_document* doc, pugi::xml_node parentNode, std::list<F_ATTR*>* f_attrList);


    public:
        static std::wstring get_feature_id(int id, int ENCODING = 0);
        static std::wstring get_information_id(int id, int ENCODING = 0);
        static std::string get_feature_id_string(int id);
        static std::string get_information_id_string(int id);
        static std::wstring get_wstring_from_coordinate_1(int value);
};