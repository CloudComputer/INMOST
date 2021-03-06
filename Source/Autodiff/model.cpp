#include "inmost_model.h"


namespace INMOST
{
	
	void Model::AddEntry(std::string name, AbstractEntry & entry)
	{
		assert( !isInitialized() ); // do not add new data after initialization
		assert( GetEntry(name) == NULL ); // do not overwrite entry with the same name
		Entries.push_back(std::make_pair(name,&entry));
	}
	
	void Model::AddMesh(std::string name, Mesh & m)
	{
		assert( !isInitialized() ); // do not add new data after initialization
		assert( GetMesh(name) == NULL ); // do not overwrite mesh with the same name
		Meshes.push_back(std::make_pair(name,&m));
	}
	
	void Model::AddSubModel(std::string name, AbstractSubModel & submodel)
	{
		assert( !isInitialized() ); // do not add new data after initialization
		assert( GetSubModel(name) == NULL ); // do not overwrite submodel with the same name
		SubModels.push_back(std::make_pair(name,&submodel));
	}
	
	void Model::AddOperator(std::string name, AbstractOperator & op)
	{
		assert( !isInitialized() ); // do not add new data after initialization
		assert( GetOperator(name) == NULL ); // do not overwrite submodel with the same name
		Operators.push_back(std::make_pair(name,&op));
	}
	
	Mesh * Model::GetMesh(std::string name)
	{
		for(std::vector< std::pair<std::string,Mesh *> >::iterator it = Meshes.begin();
			it != Meshes.end(); ++it)
			if( it->first == name )
				return it->second;
		return NULL;
	}
	
	const Mesh * Model::GetMesh(std::string name) const
	{
		for(std::vector< std::pair<std::string,Mesh *> >::const_iterator it = Meshes.begin();
			it != Meshes.end(); ++it)
			if( it->first == name )
				return it->second;
		return NULL;
	}
	
	std::vector<std::string> Model::GetMeshesNames() const
	{
		std::vector<std::string> ret;
		for(std::vector< std::pair<std::string,Mesh *> >::const_iterator it = Meshes.begin();
			it != Meshes.end(); ++it)
			ret.push_back(it->first);
		return ret;
	}
	
	AbstractEntry * Model::GetEntry(std::string name)
	{
		for(std::vector< std::pair<std::string,AbstractEntry *> >::iterator it = Entries.begin();
			it != Entries.end(); ++it)
			if( it->first == name )
				return it->second;
		return NULL;
	}
	
	const AbstractEntry * Model::GetEntry(std::string name) const
	{
		for(std::vector< std::pair<std::string,AbstractEntry *> >::const_iterator it = Entries.begin();
			it != Entries.end(); ++it)
			if( it->first == name )
				return it->second;
		return NULL;
	}
	
	std::vector<std::string> Model::GetEntriesNames() const
	{
		std::vector<std::string> ret;
		for(std::vector< std::pair<std::string,AbstractEntry *> >::const_iterator it = Entries.begin();
			it != Entries.end(); ++it)
			ret.push_back(it->first);
		return ret;
	}
	
	AbstractSubModel * Model::GetSubModel(std::string name)
	{
		for(std::vector< std::pair<std::string,AbstractSubModel *> >::iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			if( it->first == name )
				return it->second;
		return NULL;
	}
	
	const AbstractSubModel * Model::GetSubModel(std::string name) const
	{
		for(std::vector< std::pair<std::string,AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			if( it->first == name )
				return it->second;
		return NULL;
	}
	
	std::vector<std::string> Model::GetSubModelsNames() const
	{
		std::vector<std::string> ret;
		for(std::vector< std::pair<std::string,AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			ret.push_back(it->first);
		return ret;
	}
	
	AbstractOperator * Model::GetOperator(std::string name)
	{
		for(std::vector< std::pair<std::string,AbstractOperator *> >::iterator it = Operators.begin();
			it != Operators.end(); ++it)
			if( it->first == name )
				return it->second;
		return NULL;
	}
	
	const AbstractOperator * Model::GetOperator(std::string name) const
	{
		for(std::vector< std::pair<std::string,AbstractOperator *> >::const_iterator it = Operators.begin();
			it != Operators.end(); ++it)
			if( it->first == name )
				return it->second;
		return NULL;
	}
	
	std::vector<std::string> Model::GetOperatorsNames() const
	{
		std::vector<std::string> ret;
		for(std::vector< std::pair<std::string,AbstractOperator *> >::const_iterator it = Operators.begin();
			it != Operators.end(); ++it)
			ret.push_back(it->first);
		return ret;
	}
	
	bool Model::PrepareEntries()
	{
		bool success = true;
		//first initialize submodels
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			success &= it->second->PrepareEntries(*this);
		//second initialize operators
		for(std::vector< std::pair<std::string, AbstractOperator *> >::iterator it = Operators.begin();
			it != Operators.end(); ++it)
			success &= it->second->PrepareEntries(*this);
		return success;
	}
	
	bool Model::Initialize()
	{
		bool success = true;
		//first initialize submodels
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			success &= it->second->Initialize(*this);
		//second initialize operators
		for(std::vector< std::pair<std::string, AbstractOperator *> >::iterator it = Operators.begin();
			it != Operators.end(); ++it)
			success &= it->second->Initialize(*this);
		//third register all the entries
		for(std::vector< std::pair<std::string, AbstractEntry *> >::iterator it = Entries.begin();
			it != Entries.end(); ++it)
		{
			it->second->reg_index = aut.RegisterEntry(*it->second);
			it->second->SetOffsetTag(aut.GetEntry(it->second->reg_index).GetOffsetTag());
		}
		initialized = success;
		return success;
	}
	
	bool Model::PrepareIterations()
	{
		bool success = true;
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			success &= it->second->PrepareIterations();
		return success;
	}
	
	bool Model::FillResidual(Residual & R) const
	{
		bool success = true;
		R.Clear();
		Automatizator::MakeCurrent(&aut);
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			success &= it->second->FillResidual(R);
		Automatizator::RemoveCurrent();
		return success;
	}
	
	bool Model::UpdateSolution(const Sparse::Vector & sol, double alpha)
	{
		bool success = true;
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			success &= it->second->UpdateSolution(sol,alpha);
		for(std::vector< std::pair<std::string, AbstractOperator *> >::const_iterator it = Operators.begin();
			it != Operators.end(); ++it)
			success &= it->second->UpdateSolution(sol,alpha);
		return success;
	}
	
	bool Model::UpdateTimeStep()
	{
		bool success = true;
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			success &= it->second->UpdateTimeStep();
		for(std::vector< std::pair<std::string, AbstractOperator *> >::const_iterator it = Operators.begin();
			it != Operators.end(); ++it)
			success &= it->second->UpdateTimeStep();
		return success;
	}
	
	bool Model::SetTimeStep(double dt)
	{
		bool success = true;
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			success &= it->second->SetTimeStep(dt);
		return success;
		
	}
	
	bool Model::RestoreTimeStep()
	{
		bool success = true;
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			success &= it->second->RestoreTimeStep();
		return success;
	}
	
	double Model::UpdateMultiplier(const Sparse::Vector & sol) const
	{
		double alpha = 1;
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			alpha = std::min(alpha,it->second->UpdateMultiplier(sol));
#if defined(USE_MPI)
		double tmp = alpha;
		MPI_Allreduce(&tmp,&alpha,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
#endif
		return alpha;
	}
	
	double Model::AdjustTimeStep(double dt) const
	{
		double ret = dt;
		for(std::vector< std::pair<std::string, AbstractSubModel *> >::const_iterator it = SubModels.begin();
			it != SubModels.end(); ++it)
			ret = std::min(ret,it->second->AdjustTimeStep(dt));
#if defined(USE_MPI)
		double tmp = ret;
		MPI_Allreduce(&tmp,&ret,1,MPI_DOUBLE,MPI_MIN,MPI_COMM_WORLD);
#endif
		return ret;
	}
}
